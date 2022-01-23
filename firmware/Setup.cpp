/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Setup.cpp
 */

#include "Setup.h"

Setup::Setup(Config* cfg) {
  this->cfg = cfg;
  this->selected = 1;
}

boolean Setup::runDeviceSetup() {
  ESP_LOGD(A32, "Beginning device setup.");
  
  startBLEServer();

  // wait for setup or timeout
  long timeout = millis() + SETUPTIME;
  while(!cfg->isConfigured() && millis() < timeout) {
    delay(250);
  }

  boolean configured = cfg->isConfigured();
  ESP_LOGD(A32, "System configured: %d", configured);
  return configured;
}

void Setup::startBLEServer() {
  ESP_LOGD(A32, "Setting up BLE...");

  int R = BLECharacteristic::PROPERTY_READ;
  int W = BLECharacteristic::PROPERTY_WRITE;

  //ConfigCallback* configCallback = new ConfigCallback();

  BLEDevice::init(A32);
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService;
  BLECharacteristic *pCharacteristic;

  //
  // Hardware Information
  //
  pService = pServer->createService(BLE_SERVICE_HWI);

  // Device Name
  pCharacteristic = pService->createCharacteristic(BLE_PROP_HWI_NAME, R|W);
  pCharacteristic->setValue(cfg->getString(BLE_PROP_HWI_NAME).c_str());
  pCharacteristic->setCallbacks(this);

  // Device MAC
  pCharacteristic = pService->createCharacteristic(BLE_PROP_HWI_MAC, R);
  pCharacteristic->setValue(WiFi.macAddress().c_str());

  pService->start();


  //
  // Network Service
  //
  pService = pServer->createService(BLE_SERVICE_NET);

  // Network Name
  pCharacteristic = pService->createCharacteristic(BLE_PROP_NET_NAME, R|W);
  pCharacteristic->setValue(cfg->getString(BLE_PROP_NET_NAME).c_str());
  pCharacteristic->setCallbacks(this);

  // Network Password
  pCharacteristic = pService->createCharacteristic(BLE_PROP_NET_PASS, R|W);
  pCharacteristic->setValue(cfg->getString(BLE_PROP_NET_PASS).c_str());
  pCharacteristic->setCallbacks(this);

  pService->start();


  //
  // Hardware Control
  //
  pService = pServer->createService(BLE_SERVICE_HWC);

  // Sleep Timeout
  pCharacteristic = pService->createCharacteristic(BLE_PROP_HWC_TIMEOUT, R|W);
  pCharacteristic->setValue(String(cfg->getInt(BLE_PROP_HWC_TIMEOUT)).c_str());
  pCharacteristic->setCallbacks(this);

  // Device Configuration Status
  pCharacteristic = pService->createCharacteristic(BLE_PROP_HWC_CONFIGURED, R|W);
  pCharacteristic->setValue(String(cfg->isConfigured()).c_str());
  pCharacteristic->setCallbacks(this);

  // Restart Device
  pCharacteristic = pService->createCharacteristic(BLE_PROP_HWC_RESTART, W);
  pCharacteristic->setCallbacks(this);

  // Reset Device
  pCharacteristic = pService->createCharacteristic(BLE_PROP_HWC_RESET, W);
  pCharacteristic->setCallbacks(this);

  pService->start();


  //
  // Firmware
  //
  pService = pServer->createService(BLE_SERVICE_FW);

  // Firmware Version
  pCharacteristic = pService->createCharacteristic(BLE_PROP_FW_VERSION, R);
  pCharacteristic->setValue(String(1).c_str());

  // Run Updater
  pCharacteristic = pService->createCharacteristic(BLE_PROP_FW_UPDATE, W);
  pCharacteristic->setCallbacks(this);

  // Update URL
  pCharacteristic = pService->createCharacteristic(BLE_PROP_FW_UPDATEURL, R|W);
  pCharacteristic->setValue(cfg->getString(BLE_PROP_FW_UPDATEURL).c_str());
  pCharacteristic->setCallbacks(this);

  pService->start();


  //
  // Button Configuration
  //
  pService = pServer->createService(BLE_SERVICE_BTN);

  // Button Config ID
  pCharacteristic = pService->createCharacteristic(BLE_PROP_BTN_ID, R|W);
  pCharacteristic->setValue(String(selected).c_str());
  pCharacteristic->setCallbacks(this);

  // Button Config Action
  pCharacteristic = pService->createCharacteristic(BLE_PROP_BTN_ACTION, R|W);
  pCharacteristic->setValue(cfg->getString("_cmd-1").c_str());
  pCharacteristic->setCallbacks(this);

  pService->start();

  // Start BLE
  ESP_LOGI(A32, "Starting BLE config server.");
  pServer->getAdvertising()->start();
}

int lastT = 0;
std::string lastK = "";
boolean continued = false;

void Setup::onWrite(BLECharacteristic *pCharacteristic) {
  std::string key = pCharacteristic->getUUID().toString();
  std::string val = pCharacteristic->getValue();
  ESP_LOGI(TAG, "Got BLE value: [ %s : %s ]", key.c_str(), val.c_str());
  continued = (key == lastK) && (millis() < lastT + 750);
  lastT = millis();
  lastK = key;

  if(key == BLE_PROP_HWC_CONFIGURED) {
    boolean conf = String(val.c_str()).toInt() > 0;
    ESP_LOGI(A32, "Set configured: %d", conf);
    cfg->setBool(BLE_PROP_HWC_CONFIGURED, conf);
    return;
  }

  if(key == BLE_PROP_HWC_RESTART) {
    ESP_LOGI(A32, "BLE Requested restart.");
    ESP.restart();
    return;
  }

  if(key == BLE_PROP_HWC_RESET) {
    ESP_LOGI(A32, "BLE Requested reset.");
    cfg->reconfigure();
    ESP.restart();
    return;
  }

  if(key == BLE_PROP_FW_UPDATE) {
    ESP_LOGI(A32, "BLE Requested software update.");
    return;
  }

  if(key == BLE_PROP_BTN_ID) {
    selected = String(val.c_str()).toInt();
    return;
  }

  if(key == BLE_PROP_BTN_ACTION) {
    String cmd = "_cmd-" + String(selected);
    if(continued){
      val.insert(0, cfg->getString(cmd.c_str()).c_str());
    }

    ESP_LOGI(A32, "Updating action: %d -> %s", selected, val.c_str());
    cfg->setString(cmd.c_str(), val.c_str());
    return;
  }

  ESP_LOGD(A32, "Updating: %s", cfg->key(key.c_str())); 
  if(continued){
    val.insert(0, cfg->getString(key.c_str()).c_str());
  }
  cfg->setString(key.c_str(), val.c_str());
}
