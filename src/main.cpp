#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;
unsigned long delta_time = 0;

int x_pos = 0;

void frame();

void setup()
{
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  delta_time = millis();
}

void loop()
{
  unsigned long current_time = millis();

  if (current_time - delta_time >= FRAME_DELAY)
  {
    delta_time = current_time;
    frame();
  }
}

void frame()
{
  tft.fillRect(x_pos, 100, 20, 20, TFT_BLACK);

  x_pos = (x_pos + 2) % 320;

  tft.fillRect(x_pos, 100, 20, 20, TFT_GREEN);
}