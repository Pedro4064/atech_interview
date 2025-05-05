#include "unity.h"
#include "unity_internals.h"

#include "max_area.h"

void setUp(void) {}

void tearDown(void) {}

static void test_empty_map(void) {
  char map[3][4] = {
      {0, 0, 0, 0},
      {0, 0, 0, 0},
      {0, 0, 0, 0},
  };
  TEST_ASSERT_EQUAL(0, calculate_max_area((char **)map, 3, 4));
}

static void test_example_given(void) {
  char map[4][5] = {
    {1, 0, 1, 0, 0},
    {1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1},
    {1, 0, 0, 1, 0}
  };

  TEST_ASSERT_EQUAL(6, calculate_max_area((char **)map, 4, 5));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_empty_map);
  RUN_TEST(test_example_given);
  return UNITY_END();
}