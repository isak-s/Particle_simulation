#ifndef Particle_H
#define Particle_H

#include "color.h"

typedef struct Particle {
    double x;
    double y;

    Color color;
} Particle;

Particle new_particle(double x, double y, Color c);

#endif