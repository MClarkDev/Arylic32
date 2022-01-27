/**
   Arylic32 Firmware
   MClarkDev.com, 2022
   Buttons.h
*/

#ifndef Buttons_H
#define Buttons_H

#define A32 "Arylic32"

#define NUMBTNS 5
#define DEBOUNCE 250

#include <Arduino.h>
#include <driver/rtc_io.h>

#include "Pins.h"

class Buttons {
  private:
    void setupButton(gpio_num_t pin, void (*callback)(void));

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
