#include "particle.h"
#include "color.h"

#include <stdio.h>

int main() {
    Color c = new_color(255, 255, 255);
    Particle p = new_particle(1, 2, c);

    printf("particle at (%f, %f), color = (%d, %d, %d)\n",
           p.x, p.y, c.r, c.g, c.b);

}