#ifndef Keypad_h
#define Keypad_h
#include <Arduino.h>
#include "Wire.h"

// keyboard Constants
#define KEYBOARD_ADDRESS 0x34
#define KEYBOARD_INT_PIN 2
#define KEYBOARD_STATE_REGISTER 0x04
#define KEYBOARD_FLAG_REGISTER 0x02
#define KEYBOARD_KEY_DOWN 0x80
#define KEYBOARD_KEY_MASK 0x7F

// keycode values for control keys
#define KEYBOARD_CODE_SHIFT 31
#define KEYBOARD_CODE_ALT 41
#define KEYBOARD_CODE_BACKSPACE 30
#define KEYBOARD_CODE_RETURN 40
#define KEYBOARD_CODE_SEND 46
#define KEYBOARD_CODE_LEFT_ARROW 47
#define KEYBOARD_CODE_UP_ARROW 39
#define KEYBOARD_CODE_DOWN_ARROW 48
#define KEYBOARD_CODE_RIGHT_ARROW 49
#define KEYBOARD_CODE_LEFT_SPACE 43
#define KEYBOARD_CODE_RIGHT_SPACE 44
#define KEYBOARD_CODE_UNUSED 42

#define KEYBOARD_SPACE_TIMEOUT 400

// configuration commands (configures the 5x10 matrix as inputs with pullups, interrupts ...
// For more information look at the code in the repo linked above
const uint8_t KEYBOARD_CONFIG_COMMANDS[] = {0x1D,0x1F,0x1E,0xFF,0x1F,0x03,0x01,0xB9,0x02,0x0F};

// Labels with placeholder characters for the control buttons
const char KEYBOARD_LABELS[] = {
  '.','1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',
  'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',
  'a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  '-',
  '#',  'z',  'x',  'c',  'v',  'b',  'n',  'm',  '^',  '*',
  '&',  '?',  ' ',  ' ',  '!','!',  '<',  ',',  '>'
};
const uint8_t KEYBOARD_CONTROL_CHARACTERS[] = {
  0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,5,
  7,0,0,0,0,0,0,0,1,6,
  8,6,10,11,12,9,2,3,4
};

// Declare our functions before use
void keyboard_configure(void);
void keyboard_clearFlag(void);
void keyboard_ISR(void);
void keyboard_tick(void);

void keyboard_keydown_event(uint8_t key);
void keyboard_keyup_event(uint8_t key);
void keyboard_control_event(uint8_t code);
void keyboard_character_event(uint8_t key);

uint8_t keyboard_getState(void);
#endif
