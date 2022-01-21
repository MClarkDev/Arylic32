#include "Buttons.h"

int tlst[] = {0, 0, 0, 0, 0};
boolean lst[] = {false, false, false, false, false};
boolean cur[] = {false, false, false, false, false};

Buttons::Buttons() {

  setupButton(PIN_DPAD_N, onPressN);
  setupButton(PIN_DPAD_E, onPressE);
  setupButton(PIN_DPAD_S, onPressS);
  setupButton(PIN_DPAD_W, onPressW);
  setupButton(PIN_DPAD_C, onPressC);
}

void Buttons::setupButton(int pin, void (*callback)(void)) {

  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(pin, callback, RISING);
}

void Buttons::clearButtons() {
  for ( int x = 0; x < NUMBTNS; x++ ) {
    tlst[x] = millis();
    cur[x] = false;
    lst[x] = false;
  }
}

int Buttons::processButtons() {
  int pressed = 0;
  for ( int x = 0; x < NUMBTNS; x++ ) {
    if(cur[x] == lst[x]) {
      cur[x] = false;
      continue;
    }

    lst[x] = cur[x];
    if((millis() - tlst[x]) > DEBOUNCE) {
      tlst[x] = millis();
      pressed += pow(2, x);
    }
    cur[x] = false;
  }
  return pressed;
}

void IRAM_ATTR onPressN() {
  cur[0] = true;
}

void IRAM_ATTR onPressE() {
  cur[1] = true;
}

void IRAM_ATTR onPressS() {
  cur[2] = true;
}

void IRAM_ATTR onPressW() {
  cur[3] = true;
}

void IRAM_ATTR onPressC() {
  cur[4] = true;
}
