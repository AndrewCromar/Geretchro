#include <Arduino.h>
#include "inputs/inputs.h"
#include "rendering/renderer.h"
#include "rendering/colors.h"
#include "game/game.h"

unsigned long prev_time = 0;
int fps = 0;
int frame_count = 0;
unsigned long last_fps_time = 0;

void setup() {
  Serial.begin(9600);
  setup_graphics();
  setup_inputs();
  prev_time = millis(); 
}

void loop() {
  unsigned long current_time = millis();
  float deltaTime = (current_time - prev_time) / 1000.0f;
  prev_time = current_time;

  get_inputs(); 

  clear_screen(G_BLACK);
  
  update(deltaTime);

  frame_count++;
  if (current_time - last_fps_time >= 1000) {
    fps = frame_count;
    frame_count = 0;
    last_fps_time = current_time;
  }
  text("FPS: " + String(fps), 110, 5, 1, G_WHITE);

  render_scaled();
}