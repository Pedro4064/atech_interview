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
  TEST_ASSERT_EQUAL(0, calculate_max_area((char *)map, 3, 4));
}

static void test_example_given(void) {
  char map[4][5] = {
      {1, 0, 1, 0, 0},
      {1, 0, 1, 1, 1},
      {1, 1, 1, 1, 1},
      {1, 0, 0, 1, 0},
  };

  TEST_ASSERT_EQUAL(6, calculate_max_area((char *)map, 4, 5));
}

static void test_vertical_line(void) {
  char map[4][5] = {
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
      {1, 0, 0, 0, 0},
  };

  TEST_ASSERT_EQUAL(4, calculate_max_area((char *)map, 4, 5));
}

static void test_horizontal_line(void) {
  char map[4][5] = {
      {1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
  };

  TEST_ASSERT_EQUAL(5, calculate_max_area((char *)map, 4, 5));
}

static void test_full(void) {
  char map[4][5] = {
      {1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1},
  };

  TEST_ASSERT_EQUAL(5*4, calculate_max_area((char *)map, 4, 5));
}

static void test_variation_1(void) {
  char map[5][6] = {
      {0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 1},
      {0, 1, 1, 0, 1, 0},
      {0, 0, 1, 0, 1, 0},
  };

  TEST_ASSERT_EQUAL(5, calculate_max_area((char *)map, 5, 6));
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_empty_map);
  RUN_TEST(test_example_given);
  RUN_TEST(test_vertical_line);
  RUN_TEST(test_horizontal_line);
  RUN_TEST(test_full);
  RUN_TEST(test_variation_1);
  return UNITY_END();
}