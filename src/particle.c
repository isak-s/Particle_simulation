#include "particle.h"

Particle new_particle(double x, double y, Color c) {
    Particle p;
    p.x = x;
    p.y = y;
    p.color = c;

    return p;
}
