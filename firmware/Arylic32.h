#ifndef Arylic32_H
#define Arylic32_H

#define TIMEOUT 15000
#define DELAY 400

#include <Arduino.h>

#include <WiFi.h>

#include "Pins.h"
#include "ArylicHTTP.h"
#include "Buttons.h"

class Arylic32 {

	private:
		int timeout;
    ArylicHTTP* api;
    Buttons* buttons;
    void processButtons();
    void sleep();

	public:
		Arylic32();
		void setup();
		void loop();
};

void IRAM_ATTR onPressN();
void IRAM_ATTR onPressE();
void IRAM_ATTR onPressS();
void IRAM_ATTR onPressW();
void IRAM_ATTR onPressC();

#endif
