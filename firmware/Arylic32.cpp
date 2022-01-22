/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Arylic32.cpp
 */
 
 #include "Arylic32.h"

Arylic32::Arylic32() {
  timeout = TIMEOUT;
}

void Arylic32::setup() {
  ESP_LOGI(LOGTAG, "Booting...");
  ESP_LOGD(LOGTAG, "Loop time: %d", DELAY);

  ledMgr = new Status();
  cfgMgr = new Config();
  if(!cfgMgr->init()) {
    ledMgr->showFormatting();
    ESP_LOGI(LOGTAG, "Formatting NVS...");
    if(!cfgMgr->reconfigure()) {
      ledMgr->showError(1);
      sleep();
    }
    ESP.restart();
  }else if(!cfgMgr->isConfigured()){
    ledMgr->showSetupMode();
    ESP_LOGI(LOGTAG, "Entering setup mode.");
    Setup* s = new Setup(cfgMgr);
    if(!s->runDeviceSetup()) {
      ledMgr->showError(2);
      sleep();
    }
    ESP.restart();
  }

  encMgr = new Wheel();
  btnMgr = new Buttons();

  WiFi.mode(WIFI_STA);
  String ssid = cfgMgr->getWiFiSSID();
  String pass = cfgMgr->getWiFiPass();
  ESP_LOGI(LOGTAG, "Connecting: %s", ssid);
  WiFi.begin(ssid.c_str(), pass.c_str());

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
    ESP_LOGD(LOGTAG, ".");
    delay(DELAY);
    return;
  }

  // load button values
  int btn = btnMgr->processButtons();
  int dir = encMgr->getDirection();

  // jog is action present, else button
  int cmd = (dir != 0) ? 98 + dir : btn;
  if (cmd > 0) {

    timeout = TIMEOUT;
    ledMgr->showCommand();
    ESP_LOGI(LOGTAG, "Command: %d", cmd);
    ESP_LOGD(LOGTAG, "Btn: %d, Enc: %d", btn, dir);

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
        apiMgr->playbackTogglePlay();
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

void Arylic32::sleep() {
  ESP_LOGI(LOGTAG, "Going to sleep.");
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_C, 0);
  esp_deep_sleep_start();
}
