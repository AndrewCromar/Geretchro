#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <Arduino.h>
#include "colors.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void setup_graphics();
void clear_screen(uint32_t color = G_BLACK);

#endif