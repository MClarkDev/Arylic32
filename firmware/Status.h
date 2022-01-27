/**
   Arylic32 Firmware
   MClarkDev.com, 2022
   Status.h
*/

#ifndef Status_H
#define Status_H

#define A32 "Arylic32"

#define CH_R 1
#define CH_G 2
#define CH_B 3

#include <Arduino.h>

#include "Pins.h"

class Status {
  private:
    int r = 0;
    int g = 0;
    int b = 0;
    void setupChannel(int ch, int pin);
    void setRGB(int r, int g, int b);

  public:
    Status();
    void showFormatting();
    void showSetupMode();
    void showConnecting();
    void showCommand();
    void showTimeout(int cur, int tmout);
    void showError(int code);
};

#endif
