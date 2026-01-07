#ifndef SD_H
#define SD_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS 22

extern bool sd_in;

void setup_sd();

#endif