#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <TFT_eSPI.h>

void setup() {
  pinMode(15, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}

void loop() {
  Serial.print("UP: ");
  Serial.print(digitalRead(15));
  Serial.print(", RIGHT: ");
  Serial.print(digitalRead(14));
  Serial.print(", DOWN: ");
  Serial.print(digitalRead(13));
  Serial.print(", LEFT: ");
  Serial.println(digitalRead(12));
}