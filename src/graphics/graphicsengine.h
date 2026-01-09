#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include "colors.h"

extern TFT_eSPI tft;
extern TFT_eSprite canvas;

void setup_graphics();
void clear_screen(uint16_t color = G_BLACK);
void rect(int x, int y, int w, int h, uint16_t color, bool fill = true);
void text(String text, int x, int y, uint8_t size = 1, uint16_t color = G_WHITE);
void texttft(String text, int x, int y, uint8_t size = 1, uint16_t color = G_WHITE);
void render();
void renderscaled();

#endif