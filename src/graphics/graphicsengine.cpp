#include "graphicsengine.h"

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite canvas = TFT_eSprite(&tft);

void setup_graphics()
{
    tft.init();
    tft.setRotation(3);

    canvas.setColorDepth(16);

    if (canvas.createSprite(160, 120) == nullptr)
    {
        Serial.println("Critical Error: Not enough RAM for Canvas!");
    }

    canvas.fillSprite(G_BLACK);
    canvas.setTextWrap(false);
    canvas.setTextFont(1);
    canvas.setTextDatum(TL_DATUM);
}

void clear_screen(uint16_t color) 
{
    canvas.fillSprite(color);
}

void rect(int x, int y, int w, int h, uint16_t color, bool fill)
{
    if (fill) {
        canvas.fillRect(x, y, w, h, color);
    } else {
        canvas.drawRect(x, y, w, h, color);
    }
}

void text(String text, int x, int y, uint8_t size, uint16_t color)
{
    canvas.setCursor(x, y);
    canvas.setTextSize(size);
    canvas.setTextColor(color);
    canvas.print(text);
}

void texttft(String text, int x, int y, uint8_t size, uint16_t color)
{
    tft.setCursor(x, y);
    tft.setTextSize(size);
    tft.setTextColor(color);
    tft.print(text);
}

void render()
{
    canvas.pushSprite(0, 0);
}

void renderscaled()
{
    tft.startWrite();

    for (int y = 0; y < 120; y++)
    {
        // Get pointer as uint16_t because we are in 16-bit mode now
        uint16_t *linePtr = (uint16_t *)canvas.getPointer() + (y * 160);

        // Scale Y by drawing the same source line to two display lines
        for (int rowRepeat = 0; rowRepeat < 2; rowRepeat++)
        {
            tft.setAddrWindow(0, (y * 2) + rowRepeat, 320, 1);
            for (int x = 0; x < 160; x++)
            {
                uint16_t p16 = linePtr[x]; 
                
                // Scale X by pushing the same pixel twice
                tft.pushColor(p16);
                tft.pushColor(p16);
            }
        }
    }

    tft.endWrite();
}