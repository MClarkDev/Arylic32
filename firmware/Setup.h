/**
   Arylic32 Firmware
   MClarkDev.com, 2022
   Setup.h
*/

#ifndef Setup_H
#define Setup_H

#define SETUPTIME 90000

#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <WiFi.h>

#include "BLEProps.h"
#include "Config.h"
#include "Updater.h"

class Setup : public BLEServerCallbacks, BLECharacteristicCallbacks {
  private:
    Config* cfg;
    int lastT = 0;
    std::string lastK;
    boolean continued;
    int selectedButton;
    void startBLEServer();

  public:
    Setup(Config* cfg);
    boolean runDeviceSetup();

  protected:
    void onWrite(BLECharacteristic *pCharacteristic) override;
    void onConnect(BLEServer* pServer) override;
    void onDisconnect(BLEServer* pServer) override;
};

#endif
