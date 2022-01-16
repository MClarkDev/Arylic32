#include "Arylic32.h"

Arylic32::Arylic32() {
  timeout = TIMEOUT;
}

void Arylic32::setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  ledMgr = new Status();
  encMgr = new Wheel();
  btnMgr = new Buttons();
  cfgMgr = new Config();
  apiMgr = new ArylicHTTP();

  WiFi.mode(WIFI_STA);
  Serial.print("Connecting");
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
    Serial.print(".");
    delay(DELAY);
    return;
  }

  int btn = btnMgr->processButtons();
  int dir = encMgr->getDirection();

  int cmd = (dir != 0) ? 98 + dir : btn;
  if (cmd >= 0) {

    timeout = TIMEOUT;
    ledMgr->showUpdating();
    Serial.println("\nUpdating...");
    String json = apiMgr->getPlayerStatus(cfgMgr->getTargetIP());
    StaticJsonDocument<1024> playerData;
    deserializeJson(playerData, json.c_str());

    ledMgr->showCommand();
    Serial.println("Command: " + String(cmd));

    int vol = (int)(playerData["vol"].as<long>());
    const char* sta = playerData["status"].as<const char*>();
    boolean play = String(sta).equals("play");

    switch (cmd) {
      case 0:
        apiMgr->preset(cfgMgr->getTargetIP(), 1);
        break;
      case 1:
        apiMgr->playbackNext(cfgMgr->getTargetIP());
        break;
      case 2:
        apiMgr->groupLeave(cfgMgr->getTargetIP());
        break;
      case 3:
        apiMgr->playbackPrev(cfgMgr->getTargetIP());
        break;
      case 4:
        if(play) {
          apiMgr->playbackPause(cfgMgr->getTargetIP());
        } else {
          apiMgr->playbackResume(cfgMgr->getTargetIP());
        }
        break;
      case 97:
        vol = vol - 5 <= 0 ? 0 : vol - 5;
        apiMgr->setVolume(cfgMgr->getTargetIP(), vol);
        break;
      case 99:
        vol = (vol + 5 >= 100) ? 100 : vol + 5;
        apiMgr->setVolume(cfgMgr->getTargetIP(), vol);
        break;
    }
  }

  ledMgr->showTimeout(timeout, TIMEOUT);
  delay(DELAY);
}

void Arylic32::sleep() {
  Serial.println("Going to sleep.");
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_C, 0);
  esp_deep_sleep_start();
}
