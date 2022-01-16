#ifndef Wheel_H
#define Wheel_H

#include <Arduino.h>

#include <ESP32Encoder.h>

#include "Pins.h"

class Wheel {
  private:
    ESP32Encoder wheel;

  public:
    Wheel();
    int getDirection();
};

#endif
