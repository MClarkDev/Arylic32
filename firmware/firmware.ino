/**
 * firwmare.ino
 * Arylic32, 2022
 * 
 * This is the main project file loaded by the Arduino IDE which will
 * subsequently load in extra modules and start the Arylic32 runtime.
 */

#include <Arduino.h>
#include "Arylic32.h"

Arylic32 arylic32;
void setup() { arylic32.setup(); }
void loop() { arylic32.loop(); }
