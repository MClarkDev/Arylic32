/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Arylic32.cpp
 */
 
 #include "Arylic32.h"

Arylic32::Arylic32() {
}

void Arylic32::setup() {
  ESP_LOGI(A32, "Booting...");
  ESP_LOGD(A32, "Loop time: %d", DELAY);

  ledMgr = new Status();
  cfgMgr = new Config();
  if(!cfgMgr->init()) {
    ledMgr->showFormatting();
    ESP_LOGI(A32, "Formatting NVS...");
    if(!cfgMgr->reconfigure()) {
      ledMgr->showError(1);
      sleep();
    }
    ESP.restart();
  }else if(!cfgMgr->isConfigured()){
    ledMgr->showSetupMode();
    ESP_LOGI(A32, "Entering setup mode.");
    Setup* s = new Setup(cfgMgr);
    if(!s->runDeviceSetup()) {
      ledMgr->showError(2);
      sleep();
    }
    ESP.restart();
  }

  connected = false;
  WiFi.mode(WIFI_STA);
  String ssid = cfgMgr->getWiFiSSID();
  String pass = cfgMgr->getWiFiPass();
  ESP_LOGI(A32, "Connecting: %s", ssid);
  WiFi.begin(ssid.c_str(), pass.c_str());

  cmdMgr = new Commander(cfgMgr);
  timeout = cfgMgr->getTimeout();
  touch();
}

void Arylic32::loop() {

  // Check WiFi connection
  if(WiFi.status() != WL_CONNECTED) {
    ledMgr->showConnecting();
    ESP_LOGD(A32, ".");
    delay(DELAY);
    return;
  }else if(!connected) {
    ESP_LOGI(A32, "Ready.");
    connected = true;
    touch();
  }

  // Process buttons
  int cmd = cmdMgr->getButtonCommand();
  if (cmd > 0) {
    ledMgr->showCommand();
    ESP_LOGI(A32, "Command: %d", cmd);
    cmdMgr->executeCommand(cmd);
    touch();
  }

  // Timeout or sleep
  ledMgr->showTimeout(sleeptime, timeout);
  sleeptime -= DELAY;
  if(sleeptime <= 0 ) {
    sleep();
  }
  delay(DELAY);
}

void Arylic32::touch() {
  ESP_LOGD(A32, "Resetting sleep timer.");
  sleeptime = timeout;
}

void Arylic32::sleep() {
  ESP_LOGI(A32, "Going to sleep.");
  esp_sleep_enable_ext0_wakeup(PIN_DPAD_C, 0);
  esp_deep_sleep_start();
}
