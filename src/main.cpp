#include <Arduino.h>
#include "inputSystem/inputSystem.h"
#include "game/game.h"
#include "time/time.h"

void setup() {
  Serial.begin(9600);

  InputSystem::setup();
  Game::start();
}

void loop() {
  Time::update();
  InputSystem::update();

  Game::update();
}