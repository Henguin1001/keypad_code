
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
// #include "Keypad.h"


#include "View.h"

// any pins can be used
#define SHARP_SCK  13
#define SHARP_MOSI 11
#define SHARP_SS   10

Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 400, 240);
#define BLACK 0
#define WHITE 1

int minorHalfSize; // 1/2 of lesser of display width or height
TextView test(10,10,"TEST",4);

void setup() {
  Serial.begin(9600);
  display.begin();
  display.clearDisplay();
  minorHalfSize = min(display.width(), display.height()) / 2;
  // keyboard_configure();
}
// 24x32
// 18x24
// 12x16
// 6x8
void loop() {
  // uint8_t result = keyboard_poll();
  // if(result){
  //   Serial.println(result);
  // }
  // keyboard_tick();
  // delay(100);
    display.clearDisplay();
    int16_t  x1, y1;
    uint16_t w, h;
    test.getSize(display,x1, y1, w, h);
    test.render(display);
    display.fillRect(x1,y1,w,h,0);
    display.refresh();
    Serial.print(w);
    Serial.print(",");
    Serial.println(h);
    // Screen must be refreshed at least once per second
    for(int j=0; j<4; j++) {
      test.setString("test"+String(j));
      display.clearDisplay();
      test.render(display);
      display.refresh();
      delay(500); // 1/2 sec delay
    } // x4 = 2 second pause between rotations

}
