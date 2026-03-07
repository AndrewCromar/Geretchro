#pragma once
#include <Arduino.h>

namespace Graphics
{
    struct DisplaySettings
    {
        int width;
        int height;
    };

    extern const DisplaySettings displaySettings;

    void init();
    void clear(uint16_t color);
    void rect(int x, int y, int w, int h, uint16_t color, bool fill);
    void text(const String& text, int x, int y, uint8_t size, uint16_t color);
    void present();
}