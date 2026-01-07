#include "graphicsengine.h"
#include "colors.h"

TFT_eSPI tft = TFT_eSPI();

void setup_graphics()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(G_BLACK);
    tft.setTextWrap(false);
    tft.setTextFont(1);
    tft.setTextDatum(TL_DATUM);
}

void clear_screen(uint32_t color)
{
    tft.fillScreen(color);
}