# RP2040 DDS
This is an RP2040 based direct digital synthesis program that generates sine waves of reasonably high accuracy in terms of frequency. It uses an 8 bit R2R DAC to output the sine wave.

This program only uses the CPU for setting up the DMAs and PIO, and is completely uninvolved in any of the frequency generation, and most of the work is done by four DMA channels. 
Uses the DMA CRC sniffer as a phase accumulator.

The PIO DAC is very crude and lacks any customization options. It should be pretty straightforward to adapt to your own application though.
