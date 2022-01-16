#include "Status.h"

Status::Status() {

  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);

  ledcAttachPin(PIN_LED_R, CH_R);
  ledcAttachPin(PIN_LED_G, CH_G);
  ledcAttachPin(PIN_LED_B, CH_B);

  ledcSetup(CH_R, 12000, 8);
  ledcSetup(CH_G, 12000, 8);
  ledcSetup(CH_B, 12000, 8);

  setRGB(200, 200, 200);
}

void Status::setRGB(int r, int g, int b) {
  ledcWrite(CH_R, r);
  ledcWrite(CH_G, g);
  ledcWrite(CH_B, b);
}

void Status::showConnecting() {
 setRGB(100, 100, 100);
}

void Status::showUpdating() {
  setRGB(20, 20, 20);
}

void Status::showCommand() {
  setRGB(255, 255, 255);
}

void Status::showTimeout(int cur, int tmout) {
  int pct = (int)(100 * cur / tmout);
  int val = (int)(pct * 127 / 100);
  setRGB(val, val, val);
}
