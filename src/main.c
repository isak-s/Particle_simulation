#define _POSIX_C_SOURCE 200809L
#include "particle.h"
#include "color.h"
#include "particlesystem.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

    Image img = new_image(255, 255);
    Particlesystem* ps = new_particlesystem();

    FILE* ffmpeg = popen("ffmpeg -f rawvideo "
                                "-pixel_format rgb24 "
                                "-video_size 640x480 "
                                "-framerate 30 "
                                "-i - -c:v libx264 "
                                "-pix_fmt yuv420p "
                                "videos/out.mp4"
                        , "w");

    Color c = new_color(255, 0, 0);
    Color c2 = new_color(0, 255, 0);
    Color c3 = new_color(0, 0, 255);

    Particle p = new_particle(100, 100, c);
    Particle p2 = new_particle(150, 100, c2);
    Particle p3 = new_particle(100, 150, c3);

    add_particle(ps, p);
    add_particle(ps, p2);
    add_particle(ps, p3);

    for (int i = 0; i < 360; i++) {
        // img = new_image(255, 255);
        tick(ps, img);

        char filename[100];
        snprintf(filename, sizeof(filename), "images/frame%d.ppm", i);
        write_to_file(fopen(filename, "wb"), img);

        write_to_file(ffmpeg, img);
    }

    pclose(ffmpeg);

    // write_to_file(fopen("images/multiple.ppm", "wb"), img);

    free_particlesystem(ps);
    free_image(img);

    return 0;
}
