#ifndef Particle_H
#define Particle_H

#include "color.h"
#include "constants.h"

typedef struct {
    double x, y;
} Vec2;

typedef struct Particle {
    Vec2 pos, velocity, acceleration;

    Vec2 old_positions[NUM_OLD_POSITIONS];
    int history_index;

    double mass; // in kg
    Color color;

} Particle;

Particle new_particle(double x, double y, Color c);

Vec2 gravitational_force_between(Particle p1, Particle p2);

void add_curr_pos_to_old_positions(Particle* p);

#endif