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

    Particle p1 = new_particle(10, 10, new_color(255, 255, 255));
    Particle p2 = new_particle(20, 20, new_color(1, 1, 1));

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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_new_particlesystem_init);
    RUN_TEST(test_add_one_particle);
    RUN_TEST(test_add_two_particles);
    return UNITY_END();
}