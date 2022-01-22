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

void Config::setIsConfigured(boolean enabled) {
  conf->putBool(BLE_PROP_HWC_CONFIGURED, enabled);
}

String Config::getWiFiSSID() {
  return getString(BLE_PROP_NET_NAME);
}

String Config::getWiFiPass() {
  return getString(BLE_PROP_NET_PASS);
}

String Config::getTargetIP() {
  return getString(BLE_PROP_WHA_MASTER);
}

boolean Config::getBool(const char* propKey) {
  String key = String(propKey).substring(0, 8);
  return conf->getBool(key.c_str(), false);
}

String Config::getString(const char* propKey) {
  String key = String(propKey).substring(0, 8);
  return conf->getString(key.c_str(), "");
}
