#include "unity.h"
#include "unity_internals.h"

#include "max_area.h"

void setUp(void){

}

void tearDown(void){

}

static void test_empty_map(void){
    char map[3][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };
    TEST_ASSERT_EQUAL(0, calculate_max_area((char *)map, 3, 4));
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(test_empty_map);
    return UNITY_END();
}