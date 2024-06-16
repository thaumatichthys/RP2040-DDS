#include "DDS.h"
#include "hardware/pio.h"
#include "R2RDAC.pio.h"
#include "math.h"

/*
    The following happens every time the PIO DREQ's from the DMA.

    The basic idea: Use the DMA's CRC sniffer in accumulate mode as the phase 
    accumulator. Then use this with a lookup table to synthesize an accurate 
    frequency.

    Updated June 16: Previously the channels repeatedly triggered eachother in a chain, 
    but that limited the clock speed to around 1/18 the system clock. I changed the DMAs 
    to each run separately and in parallel, with a maximum, 0xFFFFFFFF value written to 
    transfer count. The DDS now can only run for around 40-ish seconds before needing to 
    be restarted, but now it can run at 1/6 the clock speed, so three times faster. If 
    you are using the DDS for low frequencies only, I suggest you use the old one.

        four DMAs run in parallel.

        Preload lut_address high bytes with the address of lut[0]
        DMA0: sniffer enabled, copy increment to dummy
        DMA1: copy SNIFF_DATA(high byte only) to address(low byte)
        DMA2: copy address into DMA3 read address
        DMA3: copy into PIO

    
    The PIO implementation is very crude and may break when not using PIO0 SM0. 
    Please ensure it works in your application before using.

    wiring:

    connect a resistor ladder DAC circuit to GPIO 0-8, with 8 being the MSB.
*/

// ======================= DMA ======================= //

uint dma0_chan;
uint dma1_chan;
uint dma2_chan;
uint dma3_chan;
dma_channel_config dma0_cfg;
dma_channel_config dma1_cfg;
dma_channel_config dma2_cfg;
dma_channel_config dma3_cfg;
volatile uint32_t increment = 1;
volatile uint32_t dummy;
volatile uint8_t lut[256] __attribute__((aligned(256 * sizeof(uint8_t))));
volatile uint32_t lut_address;

// ======================= PIO ======================= //

uint sm;
const float clkdiv = 3; // 3 seems to be the fastest it can go
uint dac_offset;

// ======================= MISC ====================== //

uint32_t dds_clock;


void InitDDS(uint32_t clockFreq) {
    // ======================= MISC ====================== //

    dds_clock = clockFreq / (2 * clkdiv);

    for (int i = 0; i < 256; i++) {
        lut[i] = (sin((float) i * 2 * 3.14159f / 256.0f) + 1.0f) * 127;
    }


    // ======================= PIO ======================= //

    dac_offset = pio_add_program(pio0, &R2RDAC_program);
    sm = pio_claim_unused_sm(pio0, true);
    R2RDAC_program_init(pio0, sm, dac_offset, clkdiv);
    pio_sm_set_enabled(pio0, sm, true);

    // ======================= DMA ======================= //

    dma0_chan = dma_claim_unused_channel(true);
    dma0_cfg = dma_channel_get_default_config(dma0_chan);
    dma1_chan = dma_claim_unused_channel(true);
    dma1_cfg = dma_channel_get_default_config(dma1_chan);
    dma2_chan = dma_claim_unused_channel(true);
    dma2_cfg = dma_channel_get_default_config(dma2_chan);
    dma3_chan = dma_claim_unused_channel(true);
    dma3_cfg = dma_channel_get_default_config(dma3_chan);

    // DMA0 config
    channel_config_set_transfer_data_size(&dma0_cfg, DMA_SIZE_32);
    channel_config_set_read_increment(&dma0_cfg, false);
    channel_config_set_write_increment(&dma0_cfg, false);
    channel_config_set_sniff_enable(&dma0_cfg, true);
    channel_config_set_dreq(&dma0_cfg, DREQ_PIO0_TX0);
    channel_config_set_enable(&dma0_cfg, true);
    channel_config_set_irq_quiet(&dma0_cfg, true);
    dma_sniffer_enable(dma0_chan, DMA_SNIFF_CTRL_CALC_VALUE_SUM, true);

    // DMA1 config
    channel_config_set_transfer_data_size(&dma1_cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&dma1_cfg, false);
    channel_config_set_write_increment(&dma1_cfg, false);
    channel_config_set_dreq(&dma1_cfg, DREQ_PIO0_TX0);
    channel_config_set_enable(&dma1_cfg, true);
    channel_config_set_irq_quiet(&dma1_cfg, true);

    // DMA2 config
    channel_config_set_transfer_data_size(&dma2_cfg, DMA_SIZE_32);
    channel_config_set_read_increment(&dma2_cfg, false);
    channel_config_set_write_increment(&dma2_cfg, false);
    channel_config_set_enable(&dma2_cfg, true);
    channel_config_set_irq_quiet(&dma2_cfg, true);

    // DMA3 config
    channel_config_set_transfer_data_size(&dma3_cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&dma3_cfg, true);
    channel_config_set_write_increment(&dma3_cfg, false);
    channel_config_set_dreq(&dma3_cfg, DREQ_PIO0_TX0);
    channel_config_set_enable(&dma3_cfg, true);
    channel_config_set_irq_quiet(&dma3_cfg, true);

    lut_address = (uint32_t) lut; // this is the "preloading" I speak of

    dma_channel_configure( // writes increment to dummy, CRC summation mode; is sniffed to DMA_BASE + 0x438
        dma0_chan,
        &dma0_cfg,
        &dummy,
        &increment,
        0xFFFFFFFF,
        false
    );

    dma_channel_configure( // reads high byte from sniffer and writes it to the low byte of lut_address
        dma1_chan,
        &dma1_cfg,
        //&dma_hw->ch[dma2_chan].read_addr,
        &lut_address,
        (const volatile int*)(DMA_BASE + 0x438 + 3), // about the +3: we are reading the most significant 8 bits of the SNIFF_DATA register. 
        // this effectively sets the phase accumulator resolution. +3 means a 32 bit phase accumulator, truncated down to 8 bits. +2 --> 24 bit, etc.
        0xFFFFFFFF,
        false
    );

    dma_channel_configure( // writes lut_address to read address of dma3
        dma2_chan,
        &dma2_cfg,
        &dma_hw->ch[dma3_chan].al3_read_addr_trig,
        &lut_address,
        0xFFFFFFFF,
        false
    );

    dma_channel_configure(
        dma3_chan,
        &dma3_cfg,
        pio0->txf,
        &dummy, // this is irrelevant (DMA2 overwrites this)
        0xFFFFFFFF,
        false
    );
}

uint32_t ChangeDDSFreq(double requestedFreq) {
    // See https://www.analog.com/en/resources/analog-dialogue/articles/all-about-direct-digital-synthesis.html
    // Fo = M * Fclock / (2^n) | n = 32
    increment = round(pow(2, 32) * requestedFreq / (double) dds_clock);

    dma_channel_abort(dma0_chan);
    dma_channel_abort(dma1_chan);
    dma_channel_abort(dma2_chan);
    dma_channel_abort(dma3_chan);

    dma_channel_start(dma0_chan);
    dma_channel_start(dma1_chan);
    dma_channel_start(dma2_chan);
    dma_channel_start(dma3_chan);

    return (uint64_t) increment * dds_clock / ((uint64_t) 1 << 32);
}
