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

add_executable(pwm_pico pwm.c)

pico_generate_pio_header(pwm_pico ${CMAKE_CURRENT_LIST_DIR}/pwm.pio)

pico_set_program_name(pwm_pico "pwm")
pico_set_program_version(pwm_pico "0.1")

pico_enable_stdio_uart(pwm_pico 1)
pico_enable_stdio_usb(pwm_pico 0)

# Add the standard library to the build
target_link_libraries(pwm_pico pico_stdlib)

# Add any user requested libraries
target_link_libraries(pwm_pico
        hardware_i2c
        hardware_pio
        )

pico_add_extra_outputs(pwm_pico)
target_compile_definitions(pwm_pico PRIVATE TARGET_PICO)

add_executable(pwm_tiny_2040 pwm.c)

pico_generate_pio_header(pwm_tiny_2040 ${CMAKE_CURRENT_LIST_DIR}/pwm.pio)

pico_set_program_name(pwm_tiny_2040 "pwm")
pico_set_program_version(pwm_tiny_2040 "0.1")

pico_enable_stdio_uart(pwm_tiny_2040 1)
pico_enable_stdio_usb(pwm_tiny_2040 0)

# Add the standard library to the build
target_link_libraries(pwm_tiny_2040 pico_stdlib)

# Add any user requested libraries
target_link_libraries(pwm_tiny_2040
        hardware_i2c
        hardware_pio
        )

pico_add_extra_outputs(pwm_tiny_2040)
target_compile_definitions(pwm_tiny_2040 PRIVATE TARGET_TINY_2040)
