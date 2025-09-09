#include "image.h"

Image new_image(int width, int height) {
    Image img;
    img.pixels = malloc(height * width * sizeof(Color));
    img.height = height;
    img.width = width;
    return img;
}


void free_image(Image img) {
    free(img.pixels);
}