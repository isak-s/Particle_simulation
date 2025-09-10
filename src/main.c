#include "particle.h"
#include "color.h"
#include "particlesystem.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

    Image img = new_image(255, 255);
    Particlesystem* ps = new_particlesystem();

    Color c = new_color(255, 0, 0);
    Particle p = new_particle(1, 2, c);

    add_particle(ps, p);

    for (int i = 0; i < 10; i++) {
        draw_particle(p, img);
        p.x += 1;
        p.y += 1;
    }

    write_to_file(fopen("images/movedP.ppm", "wb"), img);

    printf("particle at (%f, %f), color = (%d, %d, %d)\n",
           p.x, p.y, c.r, c.g, c.b);

    free_particlesystem(ps);
    free_image(img);

    return 0;
}
