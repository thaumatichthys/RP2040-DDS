#include "stdio.h" // for printf
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/vreg.h"
#include "DDS.h"
/*
    RP2040 DDS
*/

int main() {
    vreg_set_voltage(VREG_VOLTAGE_1_30); // the higher the clock speed the better for DDS (assuming 6 millihertz resolution is sufficient)
    set_sys_clock_khz(420000, true);

    stdio_init_all(); // for printf

    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    InitDDS(420000000);

    ChangeDDSFreq(8000000);
    
    while(1) {
        gpio_put(25, 1);
        sleep_ms(100);
        gpio_put(25, 0);
        sleep_ms(100);
    }
}