#ifndef Arylic32_H
#define Arylic32_H

#define TIMEOUT 12000
#define DELAY 25

#include <Arduino.h>

#include <WiFi.h>
#include <ArylicHTTP.h>
#include <ArduinoJson.h>

#include "Config.h"

#include "Pins.h"
#include "Status.h"
#include "Wheel.h"
#include "Buttons.h"

class Arylic32 {

  private:
    int timeout;
    Status* ledMgr;
    Wheel* encMgr;
    Buttons* btnMgr;
    Config* cfgMgr;
    ArylicHTTP* apiMgr;
    void sleep();
    void playerPlayPause();

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
