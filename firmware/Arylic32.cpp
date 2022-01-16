#include "Arylic32.h"

Arylic32::Arylic32() {
  timeout = TIMEOUT;
}

void Arylic32::setup() {
  Serial.begin(115200);

  ledMgr = new Status();
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
    ledMgr->showConnecting();
    btnMgr->clearButtons();
    delay(DELAY);
    return;
  }

  if(!playerCurrent) {
    ledMgr->showUpdating();
    deserializeJson(playerData, apiMgr->getPlayerStatus(cfgMgr->getTargetIP()));
    playerCurrent = true;
  }

  int btn = btnMgr->processButtons();
  if (btn >= 0) {
    timeout = TIMEOUT;
    ledMgr->showCommand();
    int vol = (int)(playerData["vol"].as<long>());
    switch (btn) {
      case 0:
        apiMgr->setVolume(cfgMgr->getTargetIP(), vol + 5);
        break;
      case 1:
        apiMgr->playbackNext(cfgMgr->getTargetIP());
        break;
      case 2:
        apiMgr->setVolume(cfgMgr->getTargetIP(), vol - 5);
        break;
      case 3:
        apiMgr->playbackPrev(cfgMgr->getTargetIP());
        break;
      case 4:
        apiMgr->playbackPause(cfgMgr->getTargetIP());
        break;
    }
    playerCurrent = false;
  }

  ledMgr->showTimeout(timeout, TIMEOUT);
  delay(DELAY);
}

void Arylic32::sleep() {
  Serial.println("Going to sleep.");
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_C, 0);
  esp_deep_sleep_start();
}
