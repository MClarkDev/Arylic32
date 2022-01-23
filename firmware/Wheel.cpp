/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Wheel.cpp
 */

#include "Wheel.h"

Wheel::Wheel() {
  ESP32Encoder::useInternalWeakPullResistors=UP;
  wheel.attachHalfQuad(PIN_ENC_A, PIN_ENC_B);
  wheel.setCount(0);
}

/**
 * Get the direction of the encorder wheel
 * Return +1, 0, -1
 */
int Wheel::getDirection() {
  int dir = 0;
  int count = wheel.getCount();
  dir = count > 1 ? 1 : dir;
  dir = count < -1 ? -1 : dir;
  if(dir != 0) {
    wheel.setCount(0);
  }
  return dir;
}
