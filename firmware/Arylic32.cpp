/**
   Arylic32 Firmware
   MClarkDev.com, 2022
   Arylic32.cpp
*/

#include "Arylic32.h"

Arylic32::Arylic32() {
}

void Arylic32::setup() {
  ESP_LOGI(A32, "Booting...");
  ESP_LOGD(A32, "Loop time: %d", DELAY);

  // Setup config and IO
  cfgMgr = new Config();
  ledMgr = new Status();
  cmdMgr = new Commander(cfgMgr);

  // Get boot count
  int boots = cfgMgr->init();
  ESP_LOGI(A32, "Boots: %d", boots);

  if (boots <= 0) {
    // Device initialization
    ledMgr->showFormatting();
    ESP_LOGI(A32, "Formatting NVS...");
    if (!cfgMgr->reconfigure()) {
      ledMgr->showError(1);
      sleep();
    }
    ESP.restart();
  } else if (!cfgMgr->isConfigured()) {
    // BLE setup mode
    ledMgr->showSetupMode();
    ESP_LOGI(A32, "Entering setup mode.");
    Setup* s = new Setup(cfgMgr);
    if (!s->runDeviceSetup()) {
      ledMgr->showError(2);
      sleep();
    }
    ESP.restart();
  }

  // WiFi setup
  connected = false;
  WiFi.mode(WIFI_STA);
  String ssid = cfgMgr->getString(BLE_PROP_NET_NAME);
  String pass = cfgMgr->getString(BLE_PROP_NET_PASS);
  ESP_LOGI(A32, "Connecting: %s", ssid.c_str());
  WiFi.begin(ssid.c_str(), pass.c_str());

  // Sleep timeout setup
  timeout = cfgMgr->getInt(BLE_PROP_HWC_TIMEOUT);
  touch();
}

void Arylic32::loop() {

  // Sleep if its time
  if ((sleeptime -= DELAY) <= 0) {
    sleep();
  }

  // Check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    ledMgr->showConnecting();
    ESP_LOGD(A32, ".");
    return;
  } else if (!connected) {
    ESP_LOGI(A32, "Ready.");
    connected = true;
    touch();
  }

  // Process buttons
  int cmd = cmdMgr->getButtonCommand();
  if (cmd > 0 && connected) {
    ledMgr->showCommand();
    ESP_LOGI(A32, "Command: %d", cmd);
    cmdMgr->executeCommand(cmd);
    touch();
  }

  ledMgr->showTimeout(sleeptime, timeout);
  delay(DELAY);
}

// Reset the sleep timer
void Arylic32::touch() {
  ESP_LOGD(A32, "Resetting sleep timer [ %d :: %d ]", sleeptime, timeout);
  sleeptime = timeout;
}

// Put the device to sleep
void Arylic32::sleep() {

  // Allow NESWC to wake
  gpio_pulldown_en(PIN_DPAD_N);
  gpio_pulldown_en(PIN_DPAD_E);
  gpio_pulldown_en(PIN_DPAD_S);
  gpio_pulldown_en(PIN_DPAD_W);
  gpio_pulldown_en(PIN_DPAD_C);
  esp_sleep_enable_ext1_wakeup(PIN_WAKE_MASK, ESP_EXT1_WAKEUP_ANY_HIGH);

  ESP_LOGI(A32, "Going to sleep.");
  esp_deep_sleep_start();
}
