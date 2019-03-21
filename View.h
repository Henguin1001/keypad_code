#ifndef view_h
#define view_h
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

class View {
private:
  bool visable = true;
public:
  virtual void render(Adafruit_SharpMem display);
  virtual void control_handler(uint8_t code);
  virtual void character_handler(uint8_t code);
};

#endif
