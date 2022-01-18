#include <nvs_flash.h>
#include <Preferences.h>

#define NET_NAME "network.name"
#define NET_PASS "<password>"
#define NET_DEV "192.168.1.200"

void setup() {

  nvs_flash_erase();
  nvs_flash_init();

  Preferences conf;
  conf.begin("arylic32", false);

  conf.putString("netName", NET_NAME);
  conf.putString("netPass", NET_PASS);
  conf.putString("netDev", NET_DEV);

  conf.putBool("sysConfigured", true);

  conf.end();
}

void loop() {}

