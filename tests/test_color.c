// #include "third_party/unity/src/unity.h"
#include <unity.h>
#include "color.h"

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void test_new_color_should_set_rgb(void) {
    Color c = new_color(255, 128, 64);
    TEST_ASSERT_EQUAL_UINT8(255, c.r);
    TEST_ASSERT_EQUAL_UINT8(128, c.g);
    TEST_ASSERT_EQUAL_UINT8(64, c.b);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_color_should_set_rgb);
    return UNITY_END();
}