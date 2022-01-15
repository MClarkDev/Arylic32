#include "Arylic32.h"

#define WIFI_SSID "network.name"
#define WIFI_PASS "<password>"

#define ARYLIC_DEV "10.3.106.120"

Arylic32::Arylic32() {
	timeout = TIMEOUT;
}

void Arylic32::setup() {

  Serial.begin(115200);

	WiFi.mode(WIFI_STA);
	WiFi.begin(WIFI_SSID, WIFI_PASS);

  api = new ArylicHTTP();

  buttons = new Buttons();
}

void Arylic32::loop() {
  timeout -= DELAY;

  if(WiFi.status() != WL_CONNECTED) {
    //notConnected();
    delay(DELAY);
    return;
  }

  int btn = buttons->processButtons();
  if (btn >= 0) {
    timeout = TIMEOUT;
    switch (btn) {
      case 0:
        api->setVolume(ARYLIC_DEV, 80);
        break;
      case 1:
        api->playbackNext(ARYLIC_DEV);
        break;
      case 2:
        api->setVolume(ARYLIC_DEV, 40);
        break;
      case 3:
        api->playbackPrev(ARYLIC_DEV);
        break;
      case 4:
        api->playbackPause(ARYLIC_DEV);
        break;
    }
  }

  if(timeout <= 0 ) {
    sleep();
  }

  delay(DELAY);
}

void Arylic32::sleep() {

  Serial.println("Sleeping.");
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_N, 0);
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_E, 0);
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_S, 0);
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_W, 0);
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_C, 0);
  esp_deep_sleep_start();
}
