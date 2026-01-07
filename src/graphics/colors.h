#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>

inline uint16_t make_color(uint8_t r, uint8_t g, uint8_t b)
{
    return ((b & 0xF8) << 8) | ((g & 0xFC) << 3) | (r >> 3);
}

#define G_BLACK make_color(000, 000, 000)
#define G_WHITE make_color(255, 255, 255)
#define G_RED make_color(255, 000, 000)
#define G_ORANGE make_color(255, 127, 000)
#define G_YELLOW make_color(255, 255, 000)
#define G_GREEN make_color(000, 255, 000)
#define G_BLUE make_color(000, 000, 255)
#define G_PURPLE make_color(128, 000, 128)

#endif