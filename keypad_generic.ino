
/*
 * TCA8418 Driver
 * This code is adapted from the phishman's driver for arduino, https://github.com/phishman/TCA8418
 * The difference is that it is written to be easily ported to another microcontroller
 * Author: Henry Troutman
 */
/*
 * Keyboard PCB Hookup Guide:
 * 1 -> 3.3V
 * 2 -> GND
 * 3 -> SDA
 * 4 -> SCL
 * 5 -> INT_PIN
 * 6 -> RTC_INT (ds3231)
 */
#include "Keypad.h"


void setup() {
  Serial.begin(9600);
  keyboard_configure();
}

void loop() {
  // uint8_t result = keyboard_poll();
  // if(result){
  //   Serial.println(result);
  // }
  keyboard_tick();
  delay(100);
}
