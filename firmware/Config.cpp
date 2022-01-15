#include "Config.h"

Config::Config() {
  
}

char* Config::getWiFiSSID() {
  return "network.name";
}

char* Config::getWiFiPass() {
  return "<password>";
}
