#include "Buttons.h"

int tlst[] = {0, 0, 0, 0, 0};
boolean lst[] = {false, false, false, false, false};
boolean cur[] = {false, false, false, false, false};

Buttons::Buttons() {

  pinMode(PIN_DPAD_N, INPUT_PULLUP);
  pinMode(PIN_DPAD_S, INPUT_PULLUP);
  pinMode(PIN_DPAD_E, INPUT_PULLUP);
  pinMode(PIN_DPAD_W, INPUT_PULLUP);
  pinMode(PIN_DPAD_C, INPUT_PULLUP);

  attachInterrupt(PIN_DPAD_N, onPressN, RISING);
  attachInterrupt(PIN_DPAD_E, onPressE, RISING);
  attachInterrupt(PIN_DPAD_S, onPressS, RISING);
  attachInterrupt(PIN_DPAD_W, onPressW, RISING);
  attachInterrupt(PIN_DPAD_C, onPressC, RISING);
}

int Buttons::processButtons() {
  int pressed = -1;
  for ( int x = 0; x < NUMBTNS; x++ ) {
    if(cur[x] == lst[x]) {
      cur[x] = false;
      continue;
    }

    lst[x] = cur[x];
    if((millis() - tlst[x]) > DEBOUNCE) {
      tlst[x] = millis();
      pressed = x;
    } else {
      cur[x] = false;
    }
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
