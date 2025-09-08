#include "particle.h"
#include "color.h"
#include "particlesystem.h"

#include <stdio.h>
#include <stdlib.h>

void write_bitmap_to_file(char* filename, Color* image, int width, int height) {

    FILE* f = fopen(filename, "wb");

    fprintf(f, "P6\n%d %d\n255\n", width, height);
    fwrite(image, sizeof(Color), width * height, f);
    fclose(f);
}

void write_gradient_to_file(char* filename, int width, int height) {
    Color* image = malloc(width * height * sizeof(Color));
    for (int y = 0; y<height; y++) {
        for (int x = 0; x < width; x++) {
            Color* c = &image[y*width + x];
            c->r = x;
            c->g = y;
            c->b = 128;
        }
    }

    write_bitmap_to_file(filename, image, width, height);

   free(image);
}

int main() {

    write_gradient_to_file("images/grad.ppm", 256, 256);

    Particlesystem* ps = malloc(sizeof(Particlesystem));

    Color c = new_color(255, 255, 255);
    Particle p = new_particle(1, 2, c);

    add_particle(ps, p);

    printf("particle at (%f, %f), color = (%d, %d, %d)\n",
           p.x, p.y, c.r, c.g, c.b);

    free(ps);
}