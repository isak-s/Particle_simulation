#ifndef Particle_H
#define Particle_H

#include "color.h"

typedef struct Particle {
    double x;
    double y;
    double velocity_x;
    double velocity_y;
    double mass; // in kg
    Color color;

} Particle;

typedef struct {
    double x, y;
} Vec2;

Particle new_particle(double x, double y, Color c);

Vec2 gravitational_force_between(Particle p1, Particle p2);

#endif