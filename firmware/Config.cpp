#include "Config.h"

Config::Config() {
  
}

char* Config::getWiFiSSID() {
  return "network.name";
}

char* Config::getWiFiPass() {
  return "<password>";
}

char* Config::getTargetIP() {
  return "10.3.106.120";
}
