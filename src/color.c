#include "color.h"
#include <stdlib.h>

Color new_color(uint8_t r, uint8_t g, uint8_t b) {
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}
