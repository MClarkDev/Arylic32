#include "Arylic32.h"

Arylic32::Arylic32() {
  timeout = TIMEOUT;
}

void Arylic32::setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  ledMgr = new Status();

  cfgMgr = new Config();
  if(!cfgMgr->init()) {
    ledMgr->showFormatting();
    Serial.println("Formatting NVS...");
    cfgMgr->format();
    ESP.restart();
  }else if(!cfgMgr->isConfigured()){
    ledMgr->showSetupMode();
    Serial.println("Entering setup mode.");
    cfgMgr->beginSetup();
    ESP.restart();
  }

  encMgr = new Wheel();
  btnMgr = new Buttons();

  WiFi.mode(WIFI_STA);
  Serial.print("Connecting: ");
  Serial.println(cfgMgr->getWiFiSSID());
  WiFi.begin(cfgMgr->getWiFiSSID().c_str(), cfgMgr->getWiFiPass().c_str());

  apiMgr = new ArylicHTTP(cfgMgr->getTargetIP());
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

  // jog is action present, else button
  int cmd = (dir != 0) ? 98 + dir : btn;
  if (cmd > 0) {

    timeout = TIMEOUT;
    ledMgr->showCommand();
    Serial.println("Command: " + String(cmd));

    switch (cmd) {
      case 1: // N
        apiMgr->preset(1);
        break;
      case 2: // E
        apiMgr->playbackNext();
        break;
      case 3: // NE
        break;
      case 4: // S
        apiMgr->groupLeave();
        break;
      case 6: // SE
        break;
      case 8: // W
        apiMgr->playbackPrev();
        break;
      case 9: // NW
        break;
      case 12: // SW
        break;
      case 16: // C
        playerPlayPause();
        break;
      case 97: // Jog Down
        apiMgr->setVolumeStepDown();
        break;
      case 99: // Jog Up
        apiMgr->setVolumeStepDown();
        break;
    }
  }

  ledMgr->showTimeout(timeout, TIMEOUT);
  delay(DELAY);
}

void Arylic32::playerPlayPause() {
  String json = apiMgr->getPlayerStatus();
  StaticJsonDocument<1024> playerData;
  deserializeJson(playerData, json.c_str());
  const char* sta = playerData["status"].as<const char*>();
  if(String(sta).equals("play")) {
    apiMgr->playbackPause();
  } else {
    apiMgr->playbackResume();
  }
}

void Arylic32::sleep() {
  Serial.println("Going to sleep.");
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_C, 0);
  esp_deep_sleep_start();
}
