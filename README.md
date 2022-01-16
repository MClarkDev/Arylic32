# Arylic32

An ESP32 based remote for [Arylic](https://www.arylic.com/) whole home audio systems.

## About

Designed for low-power ESP32's, the firmware spends most of it's time in a deep sleep state.

Pressing the center button will wake the device and connect to WiFi.

After a period of inactivity (12 seconds), the device will go back into a deep sleep.

A rotary encoder wheel in addition to 5 directional buttons are use for device operations.

Supported features:

- N: Play Preset #1
- E: Next Track
- W: Prev Track
- S: Ungroup Device
- C: Play / Pause / Wake

- Wheel+ : Volume +5%
- Wheel- : Volume -5%


## Status LED

An RGB status LED may be attached to view additional states.

Alternatively, the single onboard LED of the ESP32 Dev-module can also be used to determine the status of the device.

- 20% : Connecting
- 10% : Fetching device info
- 99% : Sending a command
- 50% : Idle, dims to 0

After any action the device begins a counter timer to shutdown; the idle LED will dim as the sleep timer counts to 0.

## Setup

WiFi and target device configuration must currently be set at build time.

These variables must be modified in [Config.cpp](firmware/Config.cpp).

Pins are Active-Low with an Internal PullUp and must be attached as defined in [Pins.h](firmware/Pins.h).

