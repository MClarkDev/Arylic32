#ifndef Status_H
#define Status_H

#define CH_R 1
#define CH_G 2
#define CH_B 3

#include <Arduino.h>

#include "Pins.h"

class Status {
  private:
    void setupChannel(int ch, int pin);
    void setRGB(int r, int g, int b);

  public:
    Status();
    void showFormatting();
    void showSetupMode();
    void showConnecting();
    void showCommand();
    void showTimeout(int cur, int tmout);
};

#endif
