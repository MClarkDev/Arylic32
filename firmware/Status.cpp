#include "Status.h"

Status::Status() {
  pinMode(PIN_LED_B, OUTPUT);
  digitalWrite(PIN_LED_B, HIGH);
}
