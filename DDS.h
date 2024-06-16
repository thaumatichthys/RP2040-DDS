#include "pico/stdlib.h"
#include "hardware/dma.h"


// initialize - uses four DMA channels
void InitDDS(uint32_t clockFreq);
// returns actual frequency
uint32_t ChangeDDSFreq(double requestedFreq);
