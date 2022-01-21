#include "Setup.h"

Setup::Setup(Config* cfg) {
  this->cfg = cfg;
}

boolean Setup::runDeviceSetup() {

  startBLEServer();

  // wait for setup or timeout
  long timeout = millis() + SETUPTIME;
  while(!cfg->isConfigured() || millis() < timeout) {
      delay(250);
  }

  return cfg->isConfigured();
}

void Setup::startBLEServer() {

  //ConfigCallback* configCallback = new ConfigCallback();

  BLEDevice::init("Arylic32");
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
  pCharacteristic->setValue(cfg->getWiFiSSID().c_str());
  //pCharacteristic->setCallbacks(configCallback);

  pService->start();

  // Start BLE
  pServer->getAdvertising()->start();
}
