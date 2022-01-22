/**
 * Arylic32 Config Utility
 * MClarkDev.com, 2022
 * ConfigScript.ino
 * 
 * 1. Run this script to configure device.
 * 2. Flash Arylic32 firmware.
 */

#define NET_NAME "network.name"
#define NET_PASS "<passphrase>"
#define NET_DEV "192.168.1.200"

#include "PropKeys.h"

void setup() {

  ESP_LOGI(A32, "Formatting");
  nvs_flash_erase();
  nvs_flash_init();

  Preferences conf;
  ESP_LOGI(A32, "Configuring");
  conf.begin(A32, false);
  conf.putString(CONF_NET_NAME, NET_NAME);
  conf.putString(CONF_NET_PASS, NET_PASS);
  conf.putString(CONF_DEV_MASTER, NET_DEV);
  conf.putBool(CONF_CONFIGURED, false);
  conf.end();

  ESP_LOGI(A32, "Done.");
}

void loop() {}
