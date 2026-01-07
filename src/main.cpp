#include <Arduino.h>
#include "inputs/inputs.h"
#include "graphics/graphicsengine.h"
#include "graphics/colors.h"
#include "sd/sd.h"

void setup()
{
  Serial.begin(9600);
  setup_inputs();
  setup_graphics();
  clear_screen(G_BLACK);

  setup_sd();
}

void loop()
{
  get_inputs();
  print_inputs();
}