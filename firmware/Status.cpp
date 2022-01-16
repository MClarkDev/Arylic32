#include "Status.h"

Status::Status() {

  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);

  ledcAttachPin(PIN_LED_R, 1);
  ledcAttachPin(PIN_LED_G, 2);
  ledcAttachPin(PIN_LED_B, 3);

  ledcSetup(1, 12000, 8);
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);

  ledcWrite(1, 255);
  ledcWrite(2, 255);
  ledcWrite(3, 255);
}

void Status::showConnecting() {

  ledcWrite(1, 80);
  ledcWrite(2, 80);
  ledcWrite(3, 80);
}

void Status::showConnected() {

  ledcWrite(1, 180);
  ledcWrite(2, 180);
  ledcWrite(3, 180);
}

void Status::showCommand() {

  ledcWrite(1, 255);
  ledcWrite(2, 255);
  ledcWrite(3, 255);
}

void Status::showTimeout(int cur, int tmout) {
  int pct = (int)(100 * cur / tmout);
  int val = (int)(pct * 127 / 100);
  ledcWrite(1, val);
  ledcWrite(2, val);
  ledcWrite(3, val);
}
