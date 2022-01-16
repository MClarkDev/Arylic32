#ifndef Status_H
#define Status_H

#include <Arduino.h>

#include "Pins.h"

class Status {
  public:
    Status();
    void showConnecting();
    void showConnected();
    void showCommand();
    void showTimeout(int cur, int tmout);
};

#endif Status_H
