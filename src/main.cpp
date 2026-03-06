#include <Arduino.h>
#include "inputSystem/inputSystem.h"
#include "game/game.h"
#include "time/time.h"
#include "rendering/renderer.h"
#include "rendering/colors.h"

void setup() {
  Serial.begin(9600);

  InputSystem::setup();
  Game::start();
}

void loop() {
  Time::update();
  InputSystem::update();
  Renderer::clear(Colors::BLACK);

  Game::update(Time::deltaTime());

  Renderer::present();
}