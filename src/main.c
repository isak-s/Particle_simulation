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

    Color red = new_color(255, 0, 0);
    // Color green = new_color(0, 255, 0);
    Color blue = new_color(0, 0, 255);
    Color white = new_color(255, 255, 255);
    // Color pink = new_color(255, 192, 203);

    Particle p = new_particle(120, 100, blue);
    Particle p2 = new_particle(150, 100, blue);
    Particle p3 = new_particle(100, 150, blue);

    Particle p4 = new_particle(200, 200, blue);
    Particle p5 = new_particle(200, 300, blue);
    Particle p6 = new_particle(250, 250, blue);
    // does weird stuff at above 160 particles atm
    for (int i = 0; i < 160; i++) {
        int x = rand() % WIDTH;
        int y = rand() & HEIGHT;
        add_particle(ps, new_particle(x, y, blue));
    }

    Particle black_hole = new_particle(300, 300, red);
    black_hole.mass *= 1000000;
    black_hole.move_randomly = 1;
    add_black_hole(ps, black_hole);

    Particle white_hole = new_particle(400, 100, white);
    white_hole.mass = 1;
    white_hole.move_randomly = 1;
    add_white_hole(ps, white_hole);

    add_particle(ps, p);
    add_particle(ps, p2);
    add_particle(ps, p3);

    add_particle(ps, p4);
    add_particle(ps, p5);
    add_particle(ps, p6);

    return ps;

}

int main() {
    // configure in constants.h and init_particlesystem

    Particlesystem* ps = init_particlesystem();

    FILE* ffmpeg = popen(FFMPEG_CMD, "w");

    Image img = new_image(WIDTH, HEIGHT);
    for (int i = 0; i < 60*FRAMERATE; i++) {
        tick(ps, &img);

        // uncomment this to write each frame to a ppm file
        // char filename[100];
        // snprintf(filename, sizeof(filename), "images/frame%d.ppm", i);
        // write_to_ppm_file(fopen(filename, "wb"), img);

        write_to_file(ffmpeg, &img);
        reset_image(&img);
    }

    free_image(&img);

    pclose(ffmpeg);

    free_particlesystem(ps);

    return 0;
}
