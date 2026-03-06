#include "inputSystem.h"
#include <Arduino.h>

namespace InputSystem
{

const int button_up_pin = 15;
const int button_right_pin = 14;
const int button_down_pin = 13;
const int button_left_pin = 12;

Inputs currentInputs;

void setup()
{
    pinMode(button_up_pin, INPUT_PULLUP);
    pinMode(button_right_pin, INPUT_PULLUP);
    pinMode(button_down_pin, INPUT_PULLUP);
    pinMode(button_left_pin, INPUT_PULLUP);
}

void update()
{
    currentInputs.up = !digitalRead(button_up_pin);
    currentInputs.right = !digitalRead(button_right_pin);
    currentInputs.down = !digitalRead(button_down_pin);
    currentInputs.left = !digitalRead(button_left_pin);
}

const Inputs& get()
{
    return currentInputs;
}

}