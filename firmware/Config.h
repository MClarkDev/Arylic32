#ifndef Config_H
#define Config_H

#include <Arduino.h>

class Config {

  public:
    Config();
    char* getWiFiSSID();
    char* getWiFiPass();
};

#endif
