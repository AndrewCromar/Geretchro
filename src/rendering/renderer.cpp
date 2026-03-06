#include "renderer.h"
#include <TFT_eSPI.h>

namespace Renderer
{

static TFT_eSPI tft = TFT_eSPI();
static TFT_eSprite canvas = TFT_eSprite(&tft);

static const int WIDTH = 160;
static const int HEIGHT = 120;

void init()
{
    tft.init();
    tft.setRotation(3);

    canvas.setColorDepth(16);

    if (canvas.createSprite(WIDTH, HEIGHT) == nullptr)
    {
        Serial.println("Renderer Error: Not enough RAM for canvas!");
    }

    canvas.fillSprite(0x0000);
    canvas.setTextWrap(false);
    canvas.setTextFont(1);
    canvas.setTextDatum(TL_DATUM);
}

void clear(uint16_t color)
{
    canvas.fillSprite(color);
}

void rect(int x, int y, int w, int h, uint16_t color, bool fill)
{
    if (fill)
        canvas.fillRect(x, y, w, h, color);
    else
        canvas.drawRect(x, y, w, h, color);
}

void text(const String& text, int x, int y, uint8_t size, uint16_t color)
{
    canvas.setCursor(x, y);
    canvas.setTextSize(size);
    canvas.setTextColor(color);
    canvas.print(text);
}

void present()
{
    present_scaled();
    // canvas.pushSprite(0, 0);
}

void present_scaled()
{
    tft.startWrite();

    for (int y = 0; y < HEIGHT; y++)
    {
        uint16_t* linePtr = (uint16_t*)canvas.getPointer() + (y * WIDTH);

        for (int repeat = 0; repeat < 2; repeat++)
        {
            tft.setAddrWindow(0, (y * 2) + repeat, WIDTH * 2, 1);

            for (int x = 0; x < WIDTH; x++)
            {
                uint16_t p = linePtr[x];

                tft.pushColor(p);
                tft.pushColor(p);
            }
        }
    }

    tft.endWrite();
}

}