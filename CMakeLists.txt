cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name (Replace my_DE3_Project with your own project's name)
project(Gestion_Inventario)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(Gestion_Inventario
    main.c
    mfrc522.c
    rfid.c
    keypad.c
)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(Gestion_Inventario
    pico_stdlib
    pico_time
    hardware_spi
    hardware_gpio
    hardware_i2c
    hardware_timer
    hardware_irq
    hardware_sync
    hardware_clocks
    hardware_pwm)

# Enable usb output, disable uart output
pico_enable_stdio_usb(Gestion_Inventario 1)
pico_enable_stdio_uart(Gestion_Inventario 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(Gestion_Inventario)