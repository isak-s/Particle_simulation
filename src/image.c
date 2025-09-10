#include "image.h"
#include <stdio.h>

// FILE* ffmpeg = popen("ffmpeg -f rawvideo -pixel_format rgb24 -video_size 640x480 -framerate 30 -i - -c:v libx264 -pix_fmt yuv420p out.mp4", "w");

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