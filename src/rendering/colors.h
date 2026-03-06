#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>

namespace Colors
{
    constexpr uint16_t BLACK  = 0x0000;
    constexpr uint16_t WHITE  = 0xFFFF;
    constexpr uint16_t RED    = 0xF800;
    constexpr uint16_t GREEN  = 0x001F;
    constexpr uint16_t BLUE   = 0x07E0;
    constexpr uint16_t YELLOW = 0xF81F;
    constexpr uint16_t PURPLE = 0xFFE0;
}

#endif