#include "Buttons.h"

boolean btn[] = {false, false, false, false, false};

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
  for ( int x = 0; x < 5; x++ ) {
    if(btn[x]) {
      pressed = x;
      btn[x] = false;
    }
  }
  return pressed;
}

void IRAM_ATTR onPressN() {
  btn[0] = true;
}

void IRAM_ATTR onPressE() {
  btn[1] = true;
}

void IRAM_ATTR onPressS() {
  btn[2] = true;
}

void IRAM_ATTR onPressW() {
  btn[3] = true;
}

void IRAM_ATTR onPressC() {
  btn[4] = true;
}
