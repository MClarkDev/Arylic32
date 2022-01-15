# Arylic32

An ESP32 based remote for Arylic whole home audio systems.

## About

Designed for low-power ESP32's, the firmware spends most of it's time in a deep sleep state.

Press the center button to wake the device which will then connect to WiFi.

There are 5 buttons currently supported:

- N: Volume @ 80%
- S: Volume @ 40%
- E: Next Track
- W: Prev Track
- C: Pause

## Setup

WiFi and target device configuration must currently be set at build time. These variables must be modified at the top of [Arylic32.cpp](Arylic32.cpp).

Pins are Active-Low with an Internal PullUp and must be attached as defined in [Pins.h](Pins.h).

