#include "Status.h"

Status::Status() {

  setupChannel(CH_R, PIN_LED_R);
  setupChannel(CH_G, PIN_LED_G);
  setupChannel(CH_B, PIN_LED_B);

  setRGB(200, 200, 200);
}

void Status::setupChannel(int ch, int pin) {
  ledcSetup(ch, 12000, 8);
  ledcWrite(ch, 127);

  pinMode(pin, OUTPUT);
  ledcAttachPin(pin, ch);
}

void Status::setRGB(int r, int g, int b) {
  ledcWrite(CH_R, r);
  ledcWrite(CH_G, g);
  ledcWrite(CH_B, b);
}

void Status::showConnecting() {
 setRGB(50, 50, 50);
}

void Status::showUpdating() {
  setRGB(25, 25, 25);
}

void Status::showCommand() {
  setRGB(255, 255, 255);
}

void Status::showTimeout(int cur, int tmout) {
  int pct = (int)(127 * cur / tmout);
  int val = (int)(pct * 127 / 100);
  setRGB(val, val, val);
}
