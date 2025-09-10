// #include "third_party/unity/src/unity.h"
#include <unity.h>
#include "particle.h"
#include <math.h>

void setUp(void) {}    // runs before each test
void tearDown(void) {} // runs after each test

#define G 6.67430e-11
#define METERS_PER_PIXEL 1.0

#define UNITY_INCLUDE_DOUBLE
#define UNITY_DOUBLE_TYPE double

double distance_between(Particle p1, Particle p2);
Vec2 normalized_vec2(Vec2 v);
double magnitude_gravitational_force_between(Particle p1, Particle p2);
Vec2 gravitational_force_between(Particle p1, Particle p2);

void test_new_particle_color_should_set_rgb(void) {
    Color c = new_color(255, 128, 64);

    Particle p = new_particle(1, 2, c);

    TEST_ASSERT_EQUAL_UINT8(255, p.color.r);
    TEST_ASSERT_EQUAL_UINT8(128, p.color.g);
    TEST_ASSERT_EQUAL_UINT8(64, p.color.b);

    (void)p;
}

void test_distance_between(void) {
    Particle p1 = new_particle(0, 0, new_color(255, 255, 255));
    Particle p2 = new_particle(3, 4, new_color(255, 255, 255));
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 5.0, distance_between(p1, p2));

    Particle p3 = new_particle(1, 1, new_color(0, 0, 0));
    Particle p4 = new_particle(1, 1, new_color(0, 0, 0));
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 0.0, distance_between(p3, p4));

    (void)p1;
    (void)p2;
    (void)p3;
    (void)p4;
}

void test_normalized_vec2(void) {
    Vec2 v = {3, 4};
    Vec2 nv = normalized_vec2(v);
    double len = sqrt(nv.x * nv.x + nv.y * nv.y);
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 1.0, len);
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 0.6, nv.x);
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 0.8, nv.y);

    Vec2 v2 = {0, 5};
    Vec2 nv2 = normalized_vec2(v2);
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 0.0, nv2.x);
    TEST_ASSERT_DOUBLE_WITHIN(1e-9, 1.0, nv2.y);

    (void)v;
    (void)nv;
    (void)nv2;
    (void)len;
}

void test_magnitude_gravitational_force_between(void) {
    Particle p1 = new_particle(0, 0, new_color(255, 255, 255));
    p1.mass = 10;

    Particle p2 = new_particle(0, 1, new_color(255, 255, 255));
    p2.mass = 20;

    double d = 1.0 * METERS_PER_PIXEL;
    double expected = (G * p1.mass * p2.mass) / (d * d);
    double result = magnitude_gravitational_force_between(p1, p2);
    TEST_ASSERT_DOUBLE_WITHIN(1e-20, expected, result);

    (void)p1;
    (void)p2;
    (void)result;
    (void)expected;
}

void test_gravitational_force_between(void) {
    Particle p1 = new_particle(0, 0, new_color(255, 255, 255));
    p1.mass = 10;

    Particle p2 = new_particle(0, 1, new_color(255, 255, 255));
    p2.mass = 20;

    Vec2 f = gravitational_force_between(p1, p2);

    // Force should point straight up
    TEST_ASSERT_DOUBLE_WITHIN(1e-15, 0.0, f.x);
    TEST_ASSERT_TRUE(f.y > 0);

    // Magnitude check
    double mag = sqrt(f.x * f.x + f.y * f.y);
    double expected = magnitude_gravitational_force_between(p1, p2);
    TEST_ASSERT_DOUBLE_WITHIN(1e-15, expected, mag);

    (void)p1;
    (void)p2;
    (void)expected;
    (void)mag;
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_particle_color_should_set_rgb);
    RUN_TEST(test_distance_between);
    RUN_TEST(test_normalized_vec2);
    RUN_TEST(test_magnitude_gravitational_force_between);
    RUN_TEST(test_gravitational_force_between);
    return UNITY_END();
}
