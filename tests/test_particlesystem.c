#include <unity.h>
#include "particlesystem.h"

static Particlesystem* ps;

void setUp(void) {ps = new_particlesystem();}
void tearDown(void) {free_particlesystem(ps);}

void test_new_particlesystem_init() {
    TEST_ASSERT_NULL(ps->firstP);
    TEST_ASSERT_NULL(ps->lastP);
}

void test_add_one_particle() {
    // Arrange
    Particle p = new_particle(10, 10, new_color(255, 255, 255));
    // act
    add_particle(ps, p);

    TEST_ASSERT_NOT_NULL(ps->firstP);
    TEST_ASSERT_NOT_NULL(ps->lastP);

    TEST_ASSERT_EQUAL_PTR(ps->firstP, ps->lastP);

    TEST_ASSERT_EQUAL(10, ps->firstP->p.x);
    TEST_ASSERT_EQUAL(10, ps->firstP->p.y);
    TEST_ASSERT_EQUAL_UINT8(255, ps->firstP->p.color.r);
    TEST_ASSERT_EQUAL_UINT8(255, ps->firstP->p.color.g);
    TEST_ASSERT_EQUAL_UINT8(255, ps->firstP->p.color.b);
}

void test_add_two_particles() {
    // arrange
    Particle p1 = new_particle(10, 10, new_color(255, 255, 255));
    Particle p2 = new_particle(20, 20, new_color(1, 1, 1));
    // act
    add_particle(ps, p1);
    add_particle(ps, p2);

    TEST_ASSERT_NOT_NULL(ps->firstP);
    TEST_ASSERT_NOT_NULL(ps->lastP);

    TEST_ASSERT(ps->firstP != ps->lastP);

    TEST_ASSERT_EQUAL(10, ps->firstP->p.x);
    TEST_ASSERT_EQUAL(10, ps->firstP->p.y);
    TEST_ASSERT_EQUAL_UINT8(255, ps->firstP->p.color.r);
    TEST_ASSERT_EQUAL_UINT8(255, ps->firstP->p.color.g);
    TEST_ASSERT_EQUAL_UINT8(255, ps->firstP->p.color.b);
}

void test_draw_particle_draws_correct_coordinate() {
    // arrange
    Particle p1 = new_particle(2, 5, new_color(255, 200, 100));
    Image img = new_image(10, 10);
    // act
    draw_particle(p1, img);

    Color c = img.pixels[img.width * 5 + 2];  // the x comes last

    TEST_ASSERT_EQUAL_UINT8(c.r, 255);
    TEST_ASSERT_EQUAL_UINT8(c.g, 200);
    TEST_ASSERT_EQUAL_UINT8(c.b, 100);
}

void test_draw_multiple_particles_draws_correct_coordinates() {
    // arrange
    Particle p1 = new_particle(2, 5, new_color(255, 200, 100));
    Particle p2 = new_particle(7, 9, new_color(111, 222, 233));
    Image img = new_image(10, 10);
    // act
    draw_particle(p1, img);
    draw_particle(p2, img);

    Color c = img.pixels[img.width * 5 + 2];  // the x comes last
    Color c2 = img.pixels[img.width * 9 + 7];  // the x comes last

    TEST_ASSERT_EQUAL_UINT8(c.r, 255);
    TEST_ASSERT_EQUAL_UINT8(c.g, 200);
    TEST_ASSERT_EQUAL_UINT8(c.b, 100);

    TEST_ASSERT_EQUAL_UINT8(c2.r, 111);
    TEST_ASSERT_EQUAL_UINT8(c2.g, 222);
    TEST_ASSERT_EQUAL_UINT8(c2.b, 233);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_particlesystem_init);
    RUN_TEST(test_add_one_particle);
    RUN_TEST(test_add_two_particles);
    RUN_TEST(test_draw_particle_draws_correct_coordinate);
    RUN_TEST(test_draw_multiple_particles_draws_correct_coordinates);

    return UNITY_END();
}