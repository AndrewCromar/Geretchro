#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>

extern int button_up_input;
extern int button_right_input;
extern int button_down_input;
extern int button_left_input;

void setup_inputs();
void get_inputs();
void print_inputs();

#endif