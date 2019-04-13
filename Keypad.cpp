
// Arduino I2C Library
#include "Keypad.h"

// keyInt allows our event to ultimately be handled in the loop
volatile bool keyInt = false;
bool shiftDown = false, altDown = false, leftSpaceDown = false, rightSpaceDown = false;
long spaceTTL = 0;

void keyboard_configure(){
  Wire.begin();
  for(uint8_t i = 0;i < 9;i+=2){
    Wire.beginTransmission(KEYBOARD_ADDRESS);
    Wire.write(KEYBOARD_CONFIG_COMMANDS[i]);
    Wire.write(KEYBOARD_CONFIG_COMMANDS[i+1]);
    Wire.endTransmission();
  }
  pinMode(KEYBOARD_INT_PIN,INPUT); // There is an external pullup on the pin
  attachInterrupt(digitalPinToInterrupt(KEYBOARD_INT_PIN), keyboard_ISR, FALLING);
}
uint8_t keyboard_getState(){
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
void keyboard_clearFlag(){
  keyInt = false;
  Wire.beginTransmission(KEYBOARD_ADDRESS);
  Wire.write(KEYBOARD_FLAG_REGISTER);
  Wire.write(0x0F);
  Wire.endTransmission();
}
void keyboard_tick(){
  if(keyInt){
    uint8_t key_code = keyboard_getState(); // Get first keycode from FIFO

    if(key_code & KEYBOARD_KEY_DOWN) {
      keyboard_clearFlag();
      keyboard_keydown_event(key_code & KEYBOARD_KEY_MASK);
    } else {
      keyboard_clearFlag();
      keyboard_keyup_event(key_code & KEYBOARD_KEY_MASK);
    }
  }
}
void keyboard_ISR(){
  keyInt = true;
}

void keyboard_keydown_event(uint8_t key){
  // Store a state for combination keys
  switch (key) {
    case KEYBOARD_CODE_SHIFT:
      shiftDown = true;
    break;
    case KEYBOARD_CODE_ALT:
      altDown = true;
    break;
    case KEYBOARD_CODE_LEFT_SPACE:
      leftSpaceDown = true;
      spaceTTL = KEYBOARD_SPACE_TIMEOUT;
    break;
    case KEYBOARD_CODE_RIGHT_SPACE:
      rightSpaceDown = true;
      spaceTTL = KEYBOARD_SPACE_TIMEOUT;
    break;
  }

  if(KEYBOARD_CONTROL_CHARACTERS[key]){
    keyboard_control_event(key);
  } else {
    keyboard_character_event(key);
  }
}
void keyboard_keyup_event(uint8_t key){
  switch (key) {
    case KEYBOARD_CODE_SHIFT:
      shiftDown = false;
    break;
    case KEYBOARD_CODE_ALT:
      altDown = false;
    break;
    case KEYBOARD_CODE_LEFT_SPACE:
      leftSpaceDown = false;
    break;
    case KEYBOARD_CODE_RIGHT_SPACE:
      rightSpaceDown = false;
    break;
  }
}
void keyboard_control_event(uint8_t code){
  // Serial.print("Control:");
  // Serial.println(KEYBOARD_CONTROL_CHARACTERS[code]);
  // Serial.println(code);
}
void keyboard_character_event(uint8_t key){
  // Change case and special character depending on shift and alt
  // if(shiftDown){
  //   Serial.print("Shift:");
  // } else if(altDown) {
  //   Serial.print("Alt:");
  // } else {
  //   Serial.print("None:");
  // }
  // Serial.println(key);
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

/*
  EVENT SUMMARY
  creating event handlers for up and down events will make
  implementing shift/alt behavior easier/possible.
*/

 /*
SPACEBAR SUMMARY
Since the spacebar has two buttons with unique ids special
consideration needs to be made to prevent double events

case 1: LEFTSPACE DOWN + LEFTSPACE UP
case 2: RIGHTSPACE DOWN + RIGHTSPACE UP
case 3: LEFTSPACE DOWN-UP + RIGHTSPACE DOWN-UP
case 4: LEFTSPACE DOWN  + RIGHTSPACE DOWN + LEFTSPACE UP + RIGHTSPACE UP
case 5: LEFTSPACE DOWN  + RIGHTSPACE DOWN + RIGHTSPACE UP + LEFTSPACE UP
case 6: RIGHTSPACE DOWN  + LEFTSPACE DOWN + RIGHTSPACE UP + LEFTSPACE UP
case 7: RIGHTSPACE DOWN  + LEFTSPACE DOWN + LEFTSPACE UP + RIGHTSPACE UP



 */
