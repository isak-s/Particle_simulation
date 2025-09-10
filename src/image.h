#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Image {
    Color* pixels;
    int width;
    int height;
} Image;

Image new_image(int width, int height);

void write_to_file(FILE* file, Image img);

void free_image(Image img);
#endif