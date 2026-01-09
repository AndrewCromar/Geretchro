#include <Arduino.h>
#include "inputs/inputs.h"
#include "graphics/graphicsengine.h"
#include "graphics/colors.h"

void setup()
{
  Serial.begin(9600);

  setup_graphics();
  clear_screen(G_BLACK);

  setup_inputs();
}

int box_x = 0;

unsigned long last_time = 0;
int frame_count = 0;
int fps = 0;

void calcuate_fps();

void loop()
{
  calcuate_fps();

  clear_screen(G_BLACK);

  rect(box_x, 50, 20, 20, G_WHITE, true);
  box_x = (box_x + 2) % 160;

  text("BLACK TEST", 10, 5, 1, G_BLACK);
  text("WHITE TEST", 10, 15, 1, G_WHITE);
  text("RED TEST", 10, 25, 1, G_RED);
  text("BLUE TEST", 10, 35, 1, G_BLUE);
  text("GREEN TEST", 10, 45, 1, G_GREEN);
  text("YELLOW TEST", 10, 55, 1, G_YELLOW);
  text("PURPLE TEST", 10, 65, 1, G_PURPLE);

  text("FPS: " + String(fps), 110, 5, 1, G_WHITE);

  renderscaled();
}

void calcuate_fps()
{
  unsigned long current_time = millis();
  frame_count++;

  if (current_time - last_time >= 1000)
  {
    fps = frame_count;
    frame_count = 0;
    last_time = current_time;
  }
}