#include "../duty_cycle_mapping.h"

#include "Unity/src/unity.h"

// Assumes little endian
void printBits(size_t const size, void const * const ptr)
{
  unsigned char *b = (unsigned char*) ptr;
  unsigned char byte;
  int i, j;

  for (i = size-1; i >= 0; i--) {
    for (j = 7; j >= 0; j--) {
      byte = (b[i] >> j) & 1;
      printf("%u", byte);
    }
  }
  puts("");
}

static unsigned int bitCount (unsigned int value) {
  unsigned int count = 0;
  while (value > 0) {           // until all bits are zero
    if ((value & 1) == 1)     // check lower bit
      count++;
    value >>= 1;              // shift bits, removing lower bit
  }
  return count;
}

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

static void test_zero_duty_cycle_is_empty_pwm_mask(void) {
  float cycle = 0.f;
  uint32_t pwm_mask = cycle_to_mask(cycle);

  TEST_ASSERT_EQUAL_UINT32(0b00000000000000000000000000000000, pwm_mask);
}

static void test_one_duty_cycle_is_full_pwm_mask(void) {
  float cycle = 1.f;

  uint32_t pwm_mask = cycle_to_mask(cycle);

  TEST_ASSERT_EQUAL_UINT32(0b11111111111111111111111111111111, pwm_mask);
}

static void test_just_under_one_duty_cycle_drops_one_bit(void) {
  float cycle = 0.97f;

  uint32_t pwm_mask = cycle_to_mask(cycle);

  TEST_ASSERT_EQUAL_UINT32(31, bitCount(pwm_mask));
}

static void test_half_duty_cycle_switches_every_bit(void) {
  float cycle = 0.5f;

  uint32_t pwm_mask = cycle_to_mask(cycle);

  TEST_ASSERT_EQUAL_UINT32(0b01010101010101010101010101010101, pwm_mask);
}

static void test_one_third_duty_cycle_switches_every_third_bit(void) {
  float cycle = 0.35f;

  uint32_t pwm_mask = cycle_to_mask(cycle);

  TEST_ASSERT_EQUAL_UINT32(0b01001001001001001001010010010010, pwm_mask);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_zero_duty_cycle_is_empty_pwm_mask);
  RUN_TEST(test_one_duty_cycle_is_full_pwm_mask);
  RUN_TEST(test_just_under_one_duty_cycle_drops_one_bit);
  RUN_TEST(test_half_duty_cycle_switches_every_bit);
  RUN_TEST(test_one_third_duty_cycle_switches_every_third_bit);
  return UNITY_END();
}