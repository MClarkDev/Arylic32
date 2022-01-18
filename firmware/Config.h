#ifndef Config_H
#define Config_H

#define CONF_CONFIGURED "sysConfigured"
#define CONF_CONFIGURED_DEF false

#define CONF_NETNAME "netName"
#define CONF_NETNAME_DEF "Arylic32"

#define CONF_NETPASS "netPass"
#define CONF_NETPASS_DEF "Arylic32"

#define CONF_NETDEV "netDev"
#define CONF_NETDEV_DEF "192.168.1.200"

#include <Arduino.h>

#include <nvs_flash.h>
#include <Preferences.h>

class Config {

  private:
    Preferences* conf;

  public:
    Config();
    boolean init();
    void format();
    String getWiFiSSID();
    String getWiFiPass();
    String getTargetIP();
    boolean isConfigured();
    void setIsConfigured(boolean configured);
    void beginSetup();
};

#endif
