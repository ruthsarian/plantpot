# Plant Pot
A demonstration of using a [Seeed Studio XIAO nRF52840](https://www.seeedstudio.com/Seeed-XIAO-BLE-nRF52840-p-5201.html) device to generate location beacons to which droids will react. This code works on both the XIAO nrf52840 and the XIAO nrf52840 Sense.

# Operation
On startup a droid location beacon is generated. A new beacon, with a randomly selected location, is generated every 2 minutes. You can change this interval by altering the value of BEACON_LIFE in the source code. The on-board RGB LED will change color to represent the current location beacon being emitted.

# Board Setup
See the 
[Seeed Studio documentation on the XIAO nRF52840](https://wiki.seeedstudio.com/XIAO_BLE/) on how to install the board into the Arduino IDE.

The XIAO comes with a version of the [Bluefruit library for nrf52-based boards](https://github.com/adafruit/Adafruit_nRF52_Arduino/tree/master/libraries/Bluefruit52Lib). Documentation on the Bluefruit library can be found on [learn.adafruit.com](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/bluefruit-nrf52-api).

# Notes
* This sketch has been tested using the non-mbed version of the board selected in the Arduino IDE.
* If you have an existing installation of the Bluefruit library for nrf51 boards you will need to uninstall it as it conflicts with the bundled nrf52 library bundled with the board.
* When programming, you may need to press the reset button TWICE to force it into bootloader mode before you can upload your sketch.