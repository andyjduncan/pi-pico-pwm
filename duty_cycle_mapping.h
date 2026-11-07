#ifndef PWM_DUTY_CYCLE_MAPPING_H
#define PWM_DUTY_CYCLE_MAPPING_H
#include <stdint.h>
#include <math.h>

static uint32_t cycle_to_mask(double cycle) {
  uint32_t mask = 0;

  const int8_t bits = 8 * sizeof mask;

  for (int8_t i = 0; i < bits; i++) {
    const double this_bit = round(cycle * i);
    const double next_bit = round(cycle * (i + 1));

    if (next_bit > this_bit) {
      mask = mask | (1 << i);
    }
  }

  return mask;
}

#endif // PWM_DUTY_CYCLE_MAPPING_H
