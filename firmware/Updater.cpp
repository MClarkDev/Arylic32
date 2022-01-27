/**
   Arylic32 Firmware
   MClarkDev.com, 2022
   Updater.cpp
*/

#include "Updater.h"

Updater::Updater(Config* cfg) {
  this->cfg = cfg;
}

void Updater::beginUpdate() {

  WiFi.mode(WIFI_STA);
  String ssid = cfg->getString(BLE_PROP_NET_NAME);
  String pass = cfg->getString(BLE_PROP_NET_PASS);
  ESP_LOGI(A32, "Connecting: %s", ssid.c_str());
  WiFi.begin(ssid.c_str(), pass.c_str());

  while(WiFi.status() != WL_CONNECTED) {
    delay(1);
  }

  String updateURL = cfg->getString(BLE_PROP_FW_UPDATEURL);
  t_httpUpdate_return ret = httpUpdate.update(client, updateURL.c_str());

  switch (ret) {
    case HTTP_UPDATE_FAILED:
      ESP_LOGE(TAG, "Update failed. Error (%d): %s\n", //
        httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_OK:
      ESP_LOGI(TAG, "Update complete.");
      ESP.restart();
      break;

    default:
      break;
  }
}
