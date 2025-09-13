#define _POSIX_C_SOURCE 200809L
#include "particle.h"
#include "color.h"
#include "particlesystem.h"
#include "image.h"
#include "constants.h"
#include "ffmpeg_macro.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Todo: add black and white holes
// black hole eats any particles that come close enough and spit them out at the white hole in randomized dir.

Particlesystem* init_particlesystem() {

    Particlesystem* ps = new_particlesystem();

    Color c = new_color(255, 0, 0);
    Color c2 = new_color(0, 255, 0);
    Color c3 = new_color(0, 0, 255);
    Color white = new_color(255, 255, 255);

    Particle p = new_particle(120, 100, c);
    Particle p2 = new_particle(150, 100, c2);
    Particle p3 = new_particle(100, 150, c3);

    Particle p4 = new_particle(200, 200, c);
    Particle p5 = new_particle(200, 300, c2);
    Particle p6 = new_particle(250, 250, c3);

    Particle heavy_particle = new_particle(300, 300, white);
    heavy_particle.mass *= 100;
    heavy_particle.velocity.y = 5;

    add_particle(ps, p);
    add_particle(ps, p2);
    add_particle(ps, p3);

    add_particle(ps, p4);
    add_particle(ps, p5);
    add_particle(ps, p6);
    add_particle(ps, heavy_particle);

    return ps;

}

int main() {
    // configure in constants.h and init_particlesystem

    Particlesystem* ps = init_particlesystem();

    FILE* ffmpeg = popen(FFMPEG_CMD, "w");

    for (int i = 0; i < 660; i++) {
        Image img = new_image(WIDTH, HEIGHT);
        tick(ps, img);

        // uncomment this to write each frame to a ppm file
        // char filename[100];
        // snprintf(filename, sizeof(filename), "images/frame%d.ppm", i);
        // write_to_ppm_file(fopen(filename, "wb"), img);

        write_to_file(ffmpeg, img);
        free_image(img);
    }

    pclose(ffmpeg);

    free_particlesystem(ps);

    return 0;
}
