#include "Arylic32.h"

#define WIFI_SSID "network.name"
#define WIFI_PASS "<password>"

#define ARYLIC_DEV "10.3.106.120"

Arylic32::Arylic32() {
  timeout = TIMEOUT;
}

void Arylic32::setup() {
  pinMode(PIN_LED_B, OUTPUT);
  digitalWrite(PIN_LED_B, HIGH);

  Serial.begin(115200);

  cfgMgr = new Config();
  btnMgr = new Buttons();
  apiMgr = new ArylicHTTP();

  WiFi.mode(WIFI_STA);
  WiFi.begin(cfgMgr->getWiFiSSID(), cfgMgr->getWiFiPass());
}

void Arylic32::loop() {
  timeout -= DELAY;
  if(timeout <= 0 ) {
    sleep();
  }

  if(WiFi.status() != WL_CONNECTED) {
    //notConnected();
    delay(DELAY);
    return;
  }

  int btn = btnMgr->processButtons();
  if (btn >= 0) {
    timeout = TIMEOUT;
    switch (btn) {
      case 0:
        apiMgr->setVolume(ARYLIC_DEV, 80);
        break;
      case 1:
        apiMgr->playbackNext(ARYLIC_DEV);
        break;
      case 2:
        apiMgr->setVolume(ARYLIC_DEV, 40);
        break;
      case 3:
        apiMgr->playbackPrev(ARYLIC_DEV);
        break;
      case 4:
        apiMgr->playbackPause(ARYLIC_DEV);
        break;
    }
  }

  delay(DELAY);
}

void Arylic32::sleep() {
  Serial.println("Going to sleep.");
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_C, 0);
  esp_deep_sleep_start();
}
