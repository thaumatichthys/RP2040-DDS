cmake_minimum_required(VERSION 3.21)

include(pico_sdk_import.cmake)

project(Direct-digital-synthesis C CXX ASM) # Change to the project name (Does not need to match or anything)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.cpp
    DDS.cpp
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_multicore
    hardware_gpio
    hardware_dma
    hardware_pio
    hardware_clocks
    hardware_vreg
)

pico_generate_pio_header(${PROJECT_NAME}  
    ${CMAKE_CURRENT_LIST_DIR}/R2RDAC.pio
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

pico_define_boot_stage2(pico-coremark-div4 ${PICO_DEFAULT_BOOT_STAGE2_FILE})     # three lines required for overclock of over 266 MHz
target_compile_definitions(pico-coremark-div4 PRIVATE PICO_FLASH_SPI_CLKDIV=4)
pico_set_boot_stage2(${PROJECT_NAME} pico-coremark-div4)