/**
   Arylic32 Firmware
   MClarkDev.com, 2022
   Arylic32.h
*/

#ifndef Arylic32_H
#define Arylic32_H

#define DELAY 25

#define A32 "Arylic32"

#include <Arduino.h>

#include <WiFi.h>
#include <ArduinoJson.h>

#include "BLEProps.h"
#include "Config.h"
#include "Setup.h"

#include "Pins.h"
#include "Status.h"
#include "Commander.h"

class Arylic32 {

  private:
    int timeout;
    int sleeptime;
    boolean connected;
    Status* ledMgr;
    Config* cfgMgr;
    Commander* cmdMgr;
    void sleep();
    void touch();

  public:
    Arylic32();
    void setup();
    void loop();
};

#endif
