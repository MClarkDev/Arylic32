#ifndef Buttons_H
#define Buttons_H

#include <Arduino.h>

#include "Pins.h"

class Buttons {
  public:
    Buttons();
    int processButtons();
};

void IRAM_ATTR onPressN();
void IRAM_ATTR onPressE();
void IRAM_ATTR onPressS();
void IRAM_ATTR onPressW();
void IRAM_ATTR onPressC();

#endif
