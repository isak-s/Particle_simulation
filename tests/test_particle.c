// #include "third_party/unity/src/unity.h"
#include <unity.h>
#include "particle.h"

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

void test_new_particle_color_should_set_rgb(void) {
    Color c = new_color(255, 128, 64);

    Particle p = new_particle(1, 2, c);

    TEST_ASSERT_EQUAL_UINT8(255, p.color.r);
    TEST_ASSERT_EQUAL_UINT8(128, p.color.g);
    TEST_ASSERT_EQUAL_UINT8(64, p.color.b);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_particle_color_should_set_rgb); 
    return UNITY_END();
}