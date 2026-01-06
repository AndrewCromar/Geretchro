#include <Arduino.h>
#include "inputs/inputs.h"

void setup()
{
  Serial.begin(9600);
  setup_inputs();
}

void loop()
{
  get_inputs();
  print_inputs();
}