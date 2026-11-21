# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(pwm C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pwm)

pico_generate_pio_header(pwm ${CMAKE_CURRENT_LIST_DIR}/pwm.pio)

target_sources(pwm PRIVATE pwm.c)

# Add the standard library to the build
target_link_libraries(pwm PRIVATE
        pico_stdlib
        hardware_i2c
        hardware_pio)

pico_add_extra_outputs(pwm)

pico_set_program_name(pwm "pwm")
pico_set_program_version(pwm "0.1")

pico_enable_stdio_uart(pwm 1)
pico_enable_stdio_usb(pwm 0)
