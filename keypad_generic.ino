
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

// Arduino I2C Library
#include <Wire.h>
#include "keypad.h"

// keyInt allows our event to ultimately be handled in the loop
volatile bool keyInt = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  keyboard_configure();
  pinMode(KEYBOARD_INT_PIN,INPUT); // There is an external pullup on the pin

  // Set up a falling edge pin interrupt on pin 2
  attachInterrupt(digitalPinToInterrupt(KEYBOARD_INT_PIN), keyboard_ISR, FALLING);
}

void loop() {
  if(keyInt){
    uint8_t key_code = keyboard_getState(); // Get first keycode from FIFO
    if(key_code & KEYBOARD_KEY_DOWN) {
      // This is where we can write to a screen or handle control keys
      Serial.println(key_code&KEYBOARD_KEY_MASK); // print the keycode
      keyInt = false;
      keyboard_clearFlag();
    }
    delay(100);
  }
}

void keyboard_configure(void){
  for(uint8_t i = 0;i < 9;i+=2){
    Wire.beginTransmission(KEYBOARD_ADDRESS);
    Wire.write(KEYBOARD_CONFIG_COMMANDS[i]);
    Wire.write(KEYBOARD_CONFIG_COMMANDS[i+1]);
    Wire.endTransmission();
  }
}
uint8_t keyboard_getState(void){
  uint8_t key;
  Wire.beginTransmission(KEYBOARD_ADDRESS);
  Wire.write(KEYBOARD_STATE_REGISTER);
  Wire.endTransmission();
  Wire.requestFrom(KEYBOARD_ADDRESS, 1);    // request 1 bytes from slave device 0x34
  while (Wire.available()) { // slave may send less than requested
    key = Wire.read(); // receive a byte as character
  }
  return key;
}
void keyboard_clearFlag(void){
  Wire.beginTransmission(KEYBOARD_ADDRESS);
  Wire.write(KEYBOARD_FLAG_REGISTER);
  Wire.write(0x0F);
  Wire.endTransmission();
}
void keyboard_ISR(void){
  keyInt = true;
}

/*
I2C Command Summary

Setup board (5x10 keypad)
write to Register, value
            0x1D, 0x1F
            0x1E, 0xFF
            0x1F, 0x03
            0x01, 0xB9

To get keys
read 1 byte from 0x04

To clear interrupt flag
write to register,value
            0x02, 0x0F

 */
