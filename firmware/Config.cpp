/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Config.cpp
 */

#include "Config.h"

Config::Config() {
  conf = new Preferences();
}

boolean Config::init() {
  boolean init = conf->begin(A32, false);
  ESP_LOGD(A32, "Config loaded: %d", init);
  return init;
}

boolean Config::reconfigure() {
  nvs_flash_init();
  return true;
}

boolean Config::isConfigured() {
  return getBool(BLE_PROP_HWC_CONFIGURED);
}

String key(const char* propKey) {
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
