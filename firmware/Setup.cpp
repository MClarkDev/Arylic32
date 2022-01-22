/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Setup.cpp
 */

#include "Setup.h"

Setup::Setup(Config* cfg) {
  this->cfg = cfg;
}

boolean Setup::runDeviceSetup() {
  ESP_LOGD(A32, "Beginning device setup.");

  startBLEServer();

  // wait for setup or timeout
  long timeout = millis() + SETUPTIME;
  while(!cfg->isConfigured() || millis() < timeout) {
      delay(250);
  }

  boolean configured = cfg->isConfigured();
  ESP_LOGD(A32, "System configured: %d", configured);
  return configured;
}

void Setup::startBLEServer() {
  ESP_LOGD(A32, "Setting up BLE...");

  //ConfigCallback* configCallback = new ConfigCallback();

  BLEDevice::init(A32);
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService;
  BLECharacteristic *pCharacteristic;

  //
  // Network Service
  //
  pService = pServer->createService(BLE_SERVICE_NET);

  // Network Name
  pCharacteristic = pService->createCharacteristic(BLE_PROP_NET_NAME,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setValue(cfg->getString(BLE_PROP_NET_NAME).c_str());
  //pCharacteristic->setCallbacks(configCallback);

  pService->start();

  // Start BLE
  ESP_LOGD(A32, "Starting BLE config server.");
  pServer->getAdvertising()->start();
}
