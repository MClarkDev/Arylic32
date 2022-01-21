#ifndef Buttons_H
#define Buttons_H

#define NUMBTNS 5
#define DEBOUNCE 180

#include <Arduino.h>

#include "Pins.h"

class Buttons {
  private:
    void setupButton(int pin, void (*callback)(void));

  public:
    Buttons();
    void clearButtons();
    int processButtons();
};

void IRAM_ATTR onPressN();
void IRAM_ATTR onPressE();
void IRAM_ATTR onPressS();
void IRAM_ATTR onPressW();
void IRAM_ATTR onPressC();

#endif
