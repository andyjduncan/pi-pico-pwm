#ifndef _PICO_STDLIB_H
#include "pico/stdlib.h"
#endif

#define I2C i2c_default
#define I2C_IRQ I2C0_IRQ
#define I2C_SDA_PIN PICO_DEFAULT_I2C_SDA_PIN
#define I2C_SCL_PIN PICO_DEFAULT_I2C_SCL_PIN

#define STATUS_LED_PIN PICO_DEFAULT_LED_PIN
#define STATUS_LED_LEVEL 1

uint8_t pins[] = {6, 7, 8, 9, 10, 11, 12, 13};