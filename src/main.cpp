#include <Arduino.h>
#include "inputSystem/inputSystem.h"

void setup() {
  Serial.begin(9600);
  InputSystem::setup();
}

void loop() {
  InputSystem::update();
}