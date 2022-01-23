/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Config.h
 */

#ifndef Config_H
#define Config_H

#define A32 "Arylic32"

#define CFG_CMD "_cmd-"
#define CFG_BOOT "bootCycles"

#include <Arduino.h>

#include <nvs_flash.h>
#include <Preferences.h>

#include "Pins.h"
#include "BLEProps.h"

class Config {

  private:
    Preferences* conf;

  public:
    Config();
    int init();
    boolean reconfigure();
    int getBootCycles();
    int getTimeout();
    boolean isConfigured();
    int getInt(const char* propKey);
    void setInt(const char* propKey, int val);
    boolean getBool(const char* propKey);
    void setBool(const char* propKey, boolean val);
    String getString(const char* propKey);
    void setString(const char* propKey, String val);
    String key(const char* propKey);
};

#endif
