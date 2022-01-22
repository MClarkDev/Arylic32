/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Setup.h
 */

#ifndef Setup_H
#define Setup_H

#define SETUPTIME 90000

#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "BLEProps.h"
#include "Config.h"

class Setup {
  private:
    Config* cfg;
    void startBLEServer();

  public:
    Setup(Config* cfg);
    boolean runDeviceSetup();
};

#endif
