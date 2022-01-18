#include "Config.h"

Config::Config() {
  conf = new Preferences();
}

boolean Config::init() {
  return conf->begin("arylic32", false);
}

void Config::format() {
  nvs_flash_init();
}

boolean Config::isConfigured() {
  return conf->getBool(CONF_CONFIGURED, CONF_CONFIGURED_DEF);
}

void Config::setIsConfigured(boolean enabled) {
  conf->putBool(CONF_CONFIGURED, enabled);
}

String Config::getWiFiSSID() {
  return conf->getString(CONF_NETNAME, CONF_NETNAME_DEF);
}

String Config::getWiFiPass() {
  return conf->getString(CONF_NETPASS, CONF_NETPASS_DEF);
}

String Config::getTargetIP() {
  return conf->getString(CONF_NETDEV, CONF_NETDEV_DEF);
}

void Config::beginSetup() {
  setIsConfigured(true);
}
