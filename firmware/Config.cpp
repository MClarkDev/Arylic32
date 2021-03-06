/**
   Arylic32 Firmware
   MClarkDev.com, 2022
   Config.cpp
*/

#include "Config.h"

Config::Config() {
  conf = new Preferences();
}

int Config::init() {
  boolean init = conf->begin(A32, false);
  ESP_LOGD(A32, "Config loaded: %d", init);

  if (!init) {
    ESP_LOGW(A32, "Failed to initialize NVS.");
    return 0;
  }

  // Toggle setup mode
  pinMode(PIN_SETUP, INPUT_PULLDOWN);
  if (digitalRead(PIN_SETUP)) {
    ESP_LOGD(A32, "Toggle setup mode.");
    setBool(BLE_PROP_HWC_CONFIGURED, !isConfigured());
  }

  conf->putInt(CFG_BOOT, (getBootCycles() + 1));
  return getBootCycles();
}

boolean Config::reconfigure() {
  nvs_flash_erase();
  nvs_flash_init();
  return true;
}

int Config::getBootCycles() {
  return conf->getInt(CFG_BOOT);
}

boolean Config::isConfigured() {
  return getBool(BLE_PROP_HWC_CONFIGURED);
}

String Config::key(const char* propKey) {
  return String(propKey).substring(0, 8);
}

int Config::getInt(const char* propKey) {
  return conf->getInt(key(propKey).c_str(), -1);
}

void Config::setInt(const char* propKey, int val) {
  conf->putInt(key(propKey).c_str(), val);
}

boolean Config::getBool(const char* propKey) {
  return conf->getBool(key(propKey).c_str(), false);
}

void Config::setBool(const char* propKey, boolean val) {
  conf->putBool(key(propKey).c_str(), val);
}

String Config::getString(const char* propKey) {
  return conf->getString(key(propKey).c_str(), "");
}

void Config::setString(const char* propKey, String val) {
  conf->putString(key(propKey).c_str(), val);
}
