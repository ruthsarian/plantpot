// demo of BLE GE beacon using the Seeed Studio XIAO nRF52840, v0.2 : ruthsarian@gmail.com
// see: https://wiki.seeedstudio.com/XIAO_BLE/
//
// references:
//   https://github.com/adafruit/Adafruit_nRF52_Arduino/tree/master/libraries/Bluefruit52Lib
//   https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/bluefruit-nrf52-api
//
// notes:
//   - bluefruit52 library is bundled with the seeed studio package that you installed
//   - if you have an adafruit bluefruit nrf51 library installed you will need to uninstall it as the include, bluefruit.h, 
//     conflicts with the nrf52 library bundles with the seeed xiao board package. (if both are needed, maybe rename bluefruit.h ??)
//
// needs further review
//   https://gist.github.com/hinzundcode/19605bc3755a4a2c4e378d1f93f1605d
//   https://devzone.nordicsemi.com/guides/short-range-guides/b/bluetooth-low-energy/posts/ble-advertising-a-beginners-tutorial
//
// compiled using non-mbed version of board
//
// When programming, you may need to press the reset button TWICE to force it into bootloader mode before
// you can upload your sketch.
//
// LED_RED, LED_GREEN, LED_BLUE defined in:
// %LOCALAPPDATA%\Arduino15\packages\Seeeduino\hardware\nrf52\1.0.0\variants\Seeed_XIAO_nRF52840_Sense\variant.h 
//
// C6:35:D1:E4:7A:66
//
//

#include <bluefruit.h>

#define BEACON_LIFE 120   // the time, in seconds, that a beacon will be advertised before a new beacon is generated

uint8_t LOCATION_BEACON_PAYLOAD[] = {
  0x83, 0x01,         // manufacturer's id: 0x0183
  0x0A,               // type of beacon (location beacon)
  0x04,               // length of beacon data
  0x01,               // location; also corresponds to the audio group the droid will select a sound from
  0x02,               // minimum interval between droid reactions to the beacon; this value is multiplied by 5 to determine the interval in seconds. droids have a minimum reaction time of 60 seconds
  0xA6,               // expected RSSI, beacon is ignored if weaker than value specified
  0x01,               // ? 0 or 1 otherwise droid will ignore the beacon
};

const uint8_t BEACON_NAME_PAYLOAD[] = "DROID";

// the setup function runs once when you press reset or power the board
void setup() {

  // init bluetooth
  Bluefruit.begin();
  Bluefruit.autoConnLed(false);   // don't touch the blue LED
  Bluefruit.setTxPower(0);        // set transmit power
  Bluefruit.Advertising.setStopCallback(beaconStopCallback);

  // init RGB LED
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);

  // generate the beacon and start advertising
  beaconStopCallback();

  // there's nothing in loop() so don't bother with it
  suspendLoop();
}

void beaconStopCallback( void ) {

  uint8_t loc;

  // pick a location for the next beacon at random
  loc = (rand() % 7) + 1;

  // clear beacon data
  Bluefruit.Advertising.clearData();

  // set flags
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);

  // modify location in location beacon
  LOCATION_BEACON_PAYLOAD[4] = loc;

  // set RGB LED to represent the location
  // using binary number formatting to make it more obvious what's going on
  if (loc & 0b001) {
    digitalWrite(LED_RED, LOW);
  } else {
    digitalWrite(LED_RED, HIGH);
  }
  if (loc & 0b010) { 
    digitalWrite(LED_GREEN, LOW);
  } else {
    digitalWrite(LED_GREEN, HIGH);
  }
  if (loc & 0b100) { 
    digitalWrite(LED_BLUE, LOW);
  } else {
    digitalWrite(LED_BLUE, HIGH);
  }

  // modify reaction time between beacon -- is this useless?
  // if the LOCATION is changing, then this will be the first time (unless we get a double) it's seen the beacon in many minutes
  //LOCATION_BEACON_PAYLOAD[5] = 12 + ((rand() % 12) * 12);

  // load beacon data
  Bluefruit.Advertising.addData(BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA, &LOCATION_BEACON_PAYLOAD, sizeof(LOCATION_BEACON_PAYLOAD));
  Bluefruit.Advertising.addData(BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME, &BEACON_NAME_PAYLOAD, sizeof(BEACON_NAME_PAYLOAD));

  // start broadcasting
  Bluefruit.Advertising.start(BEACON_LIFE);
}


void loop() {
}
