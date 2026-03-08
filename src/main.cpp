#include <Arduino.h>
#include "inputSystem/inputSystem.h"
#include "game/game.h"
#include "time/time.h"
#include "physics/solver.h"
#include "rendering/renderer.h"
#include "rendering/graphics.h"
#include "rendering/colors.h"

void setup() {
  Serial.begin(9600);

  Graphics::init();
  InputSystem::setup();
  Game::start();
}

void loop() {
  Time::update();
  InputSystem::update();
  Graphics::clear(Colors::BLACK);
  
  Game::update(Time::deltaTime());

  Solver::step(Time::deltaTime());

  Renderer::draw();

  Graphics::present();
}