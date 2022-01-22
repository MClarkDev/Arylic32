/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Config.h
 */

#ifndef Config_H
#define Config_H

#define A32 "Arylic32"

#include <Arduino.h>

#include <nvs_flash.h>
#include <Preferences.h>

#include "BLEProps.h"

class Config {

  private:
    Preferences* conf;
    int getInt(const char* propKey);
    boolean getBool(const char* propKey);
    String getString(const char* propKey);

  public:
    Config();
    boolean init();
    boolean reconfigure();
    String getWiFiSSID();
    String getWiFiPass();
    String getTargetIP();
    int getTimeout();
    boolean isConfigured();
    void setIsConfigured(boolean configured);
};

#endif
