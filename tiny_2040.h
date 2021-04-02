#ifndef _PICO_STDLIB_H
#include "pico/stdlib.h"
#endif

#define I2C i2c1
#define I2C_IRQ I2C1_IRQ
#define I2C_SDA_PIN 26
#define I2C_SCL_PIN 27

#define STATUS_LED_PIN 19
#define STATUS_LED_LEVEL 0

uint8_t pins[] = {0, 1, 2, 3, 4, 5, 6, 7};