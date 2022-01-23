/**
 * Arylic32 Firmware
 * MClarkDev.com, 2022
 * Commander.cpp
 */

#include "Commander.h"

Commander::Commander(Config* cfgMgr) {
  this->cfgMgr = cfgMgr;

  encMgr = new Wheel();
  btnMgr = new Buttons();
}

int Commander::getButtonCommand() {

  // load button values
  int btn = btnMgr->processButtons();
  int dir = encMgr->getDirection();

  // jog if action present, else button
  return (dir != 0) ? 98 + dir : btn;
}

boolean Commander::executeCommand(int cmd) {
  ESP_LOGD(A32, "Running command: %d", cmd);

  String key = "_cmd-" + String(cmd);
  String act = cfgMgr->getString(key.c_str());

  if(act.c_str() == "") {
    ESP_LOGW(A32, "Action not configured.");
    return false;
  }

  get(act);

  btnMgr->clearButtons();
  return true;
}

String Commander::get(String url) {
  HTTPClient http;
  http.begin(url.c_str());
  int code = http.GET();
  if(code <= 0) {
    ESP_LOGI(A32, "API Error: %d", code);
    return "";
  }

  String body = http.getString();
  http.end();
  return body;
}
