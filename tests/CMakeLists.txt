cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(tests C CXX ASM)

add_executable(tests
        test_duty_cycle_mapping.c
        Unity/src/unity.c
)
