/**
   Arylic32 Firmware
   MClarkDev.com, 2022
   Buttons.cpp
*/

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

// Configure a button pin and ISR
void Buttons::setupButton(gpio_num_t pin, void (*callback)(void)) {
  ESP_LOGD(A32, "Configuring button on pin %d", pin);

  rtc_gpio_deinit(pin);
  pinMode(pin, INPUT_PULLDOWN);
  attachInterrupt(pin, callback, FALLING);
}

// Reset button registers
void Buttons::clearButtons() {
  for ( int x = 0; x < NUMBTNS; x++ ) {
    tlst[x] = millis();
    cur[x] = false;
    lst[x] = false;
  }
}

// Process button registers
int Buttons::processButtons() {
  int pressed = 0;
  for ( int x = 0; x < NUMBTNS; x++ ) {
    if (cur[x] == lst[x]) {
      cur[x] = false;
      continue;
    }

    lst[x] = cur[x];
    if ((millis() - tlst[x]) > DEBOUNCE) {
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
