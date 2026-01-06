#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <TFT_eSPI.h>


int button_up_pin = 15;
int button_right_pin = 14;
int button_down_pin = 13;
int button_left_pin = 12;
int button_up_input;
int button_right_input;
int button_down_input;
int button_left_input;

void setup_inputs();
void get_inputs();
void print_inputs();

void setup()
{
  setup_inputs();
}

void loop()
{
  get_inputs();
  print_inputs();
}

void setup_inputs()
{
  pinMode(button_up_pin, INPUT_PULLUP);
  pinMode(button_right_pin, INPUT_PULLUP);
  pinMode(button_down_pin, INPUT_PULLUP);
  pinMode(button_left_pin, INPUT_PULLUP);
}

void get_inputs()
{
  button_up_input = digitalRead(button_up_pin);
  button_right_input = digitalRead(button_right_pin);
  button_down_input = digitalRead(button_down_pin);
  button_left_input = digitalRead(button_left_pin);
}

void print_inputs()
{
  Serial.println(String("UP: ") + button_up_input + " RIGHT: " + button_right_input + " DOWN: " + button_down_input + " LEFT: " + button_left_input);
}