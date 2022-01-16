#ifndef Arylic32_H
#define Arylic32_H

#define TIMEOUT 12000
#define DELAY 25

#include <Arduino.h>

#include <WiFi.h>

#include "Pins.h"
#include "Config.h"
#include "Status.h"
#include "Buttons.h"
#include "ArylicHTTP.h"

class Arylic32 {

  private:
    int timeout;
    boolean current;
    String device;
    Status* ledMgr;
    Config* cfgMgr;
    Buttons* btnMgr;
    ArylicHTTP* apiMgr;
    void sleep();

  public:
    Arylic32();
    void setup();
    void loop();
};

void IRAM_ATTR onPressN();
void IRAM_ATTR onPressE();
void IRAM_ATTR onPressS();
void IRAM_ATTR onPressW();
void IRAM_ATTR onPressC();

#endif
