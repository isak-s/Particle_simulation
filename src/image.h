#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <stdlib.h>

typedef struct Image {
    Color* pixels;
    int width;
    int height;
} Image;

Image new_image(int width, int height);
void free_image();
#endif