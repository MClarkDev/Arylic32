#ifndef Updater_H
#define Updater_H

#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

#include "Config.h"

class Updater {
  private:
    Config* cfg;
    WiFiClient client;

  public:
    Updater(Config* cfg);
    void beginUpdate();
};

#endif
