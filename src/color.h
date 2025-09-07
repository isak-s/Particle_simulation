#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Color;

Color new_color(uint8_t r, uint8_t g, uint8_t b);

#endif