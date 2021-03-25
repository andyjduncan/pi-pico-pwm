#include "hardware/i2c.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "pico/stdlib.h"
#include <stdio.h>

#include "pwm.pio.h"

#define I2C i2c_default
#define I2C_SDA_PIN PICO_DEFAULT_I2C_SDA_PIN
#define I2C_SCL_PIN PICO_DEFAULT_I2C_SCL_PIN
#define I2C_PERIPHERAL_ADDR 0x3F

#define FAN_FREQ 25000
#define LED_FREQ 150000

#define MAX_LEVEL 255

PIO pios[8];

uint8_t pins[] = {6, 7, 8, 9, 10, 11, 12, 13};

uint8_t pwm_sms[8];

uint8_t set_pwm = 0;

void create_pwm(PIO pio, uint index, uint offset) {

  int sm = pio_claim_unused_sm(pio, true);

  pwm_program_init(pio, sm, offset, pins[index], LED_FREQ, MAX_LEVEL);

  pwm_sms[index] = sm;
  pios[index] = pio;
}

void initialise_pwm() {
  uint offset0 = pio_add_program(pio0, &pwm_program);
  uint offset1 = pio_add_program(pio1, &pwm_program);

  for (uint8_t i = 0; i < 4; i++) {
    create_pwm(pio0, i, offset0);
    create_pwm(pio1, i + 4, offset1);
  }
}

void i2c0_irq_handler() {

  // Get interrupt status
  uint32_t status = I2C->hw->intr_stat;

  // Check to see if we have received data from the I2C controller
  if (status & I2C_IC_INTR_STAT_R_RX_FULL_BITS) {

    // Read the data (this will clear the interrupt)
    uint32_t value = I2C->hw->data_cmd;

    // Check if this is the 1st byte we have received
    if (value & I2C_IC_DATA_CMD_FIRST_DATA_BYTE_BITS) {

      // If so treat it as the address to use
      set_pwm = (uint8_t)(value & I2C_IC_DATA_CMD_DAT_BITS);

    } else {
      // If not 1st byte then store the data in the RAM
      // and increment the address to point to next byte
      uint8_t level = (uint8_t)(value & I2C_IC_DATA_CMD_DAT_BITS);
      pio_sm_put_blocking(pios[set_pwm], pwm_sms[set_pwm], level);
    }
  }
}

void initialise_i2c() {
  // I2C Initialisation. Using it at 100Khz.
  i2c_init(I2C, 100 * 1000);
  i2c_set_slave_mode(I2C, true, I2C_PERIPHERAL_ADDR);

  gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(I2C_SDA_PIN);
  gpio_pull_up(I2C_SCL_PIN);

  // Enable the I2C interrupts we want to process
  I2C->hw->intr_mask = (I2C_IC_INTR_MASK_M_RX_FULL_BITS);

  // Set up the interrupt handler to service I2C interrupts
  irq_set_exclusive_handler(I2C0_IRQ, i2c0_irq_handler);

  // Enable I2C interrupt
  irq_set_enabled(I2C0_IRQ, true);
}

void initialised() {
  gpio_init(PICO_DEFAULT_LED_PIN);
  gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
  gpio_put(PICO_DEFAULT_LED_PIN, 1);
}

int main() {
  initialise_pwm();

  initialise_i2c();

  initialised();

  while (true) {
    tight_loop_contents();
  }

  return 0;
}
