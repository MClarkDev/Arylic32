#ifndef Arylic32_H
#define Arylic32_H

#define TIMEOUT 12000
#define DELAY 25

#define LOGTAG "Arylic32"

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

#endif
