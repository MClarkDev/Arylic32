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

#define DEV_NAME "Remote 1"
#define DEV_TIMEOUT 30000

#define ACTION_N  "http://10.3.106.120/httpapi.asp?command=MCUKeyShortClick:1"
#define ACTION_E  "http://10.3.106.120/httpapi.asp?command=setPlayerCmd:next"
#define ACTION_S  "http://10.3.106.120/httpapi.asp?command=multiroom:Ungroup"
#define ACTION_W  "http://10.3.106.120/httpapi.asp?command=setPlayerCmd:prev"
#define ACTION_C  "http://10.3.106.120/httpapi.asp?command=setPlayerCmd:onepause"
#define ACTION_UP "http://10.3.106.120/httpapi.asp?command=setPlayerCmd:Vol--"
#define ACTION_DN "http://10.3.106.120/httpapi.asp?command=setPlayerCmd:Vol%2B%2B"

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
  conf.putString(CONF_DEV_NAME, DEV_NAME);
  conf.putString("_cmd-1", ACTION_N);
  conf.putString("_cmd-2", ACTION_E);
  conf.putString("_cmd-4", ACTION_S);
  conf.putString("_cmd-8", ACTION_W);
  conf.putString("_cmd-16", ACTION_C);
  conf.putString("_cmd-97", ACTION_UP);
  conf.putString("_cmd-99", ACTION_DN);
  conf.putInt(CONF_DEV_TIMEOUT, DEV_TIMEOUT);
  conf.putString(CONF_UPDATEURL, DFLT_UPDATEURL);
  conf.putBool(CONF_CONFIGURED, true);
  conf.end();

  ESP_LOGI(A32, "Done.");
}

void loop() {}
