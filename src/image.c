#include "image.h"
#include <stdio.h>

// FILE* ffmpeg = popen("ffmpeg -f rawvideo -pixel_format rgb24 -video_size 640x480 -framerate 30 -i - -c:v libx264 -pix_fmt yuv420p out.mp4", "w");

Image new_image(int width, int height) {
    Image img;
    img.pixels = calloc(height * width, sizeof(Color));
    img.height = height;
    img.width = width;
    return img;
}


void free_image(Image* img) {
    free(img->pixels);
}

void reset_image(Image* img) {
    for(Color* i = img->pixels; i < img->pixels + img->height*img->width; i++) {
        i->r = 0;
        i->b = 0;
        i->g = 0;
    }
}

void write_to_file(FILE* file, Image* img) {
    fwrite(img->pixels, sizeof(Color), img->width * img->height, file);
}

void write_to_ppm_file(FILE* file, Image img) {
    fprintf(file, "P6\n%d %d\n255\n", img.width, img.height);
    fwrite(img.pixels, sizeof(Color), img.width * img.height, file);
}

void write_bitmap_to_file(char* filename, Color* pixels, int width, int height) {

    FILE* f = fopen(filename, "wb");

    fprintf(f, "P6\n%d %d\n255\n", width, height);
    fwrite(pixels, sizeof(Color), width * height, f);
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

void draw_pixel(Image* img, int x, int y, Color color) {
    img->pixels[((int) y) * img->width + (int) x] = color;
}