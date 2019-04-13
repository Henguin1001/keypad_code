#ifndef view_h
#define view_h
#include <Arduino.h>
#include "Adafruit_GFX.h"
#include "Adafruit_SharpMem.h"

#define BLACK 0
#define WHITE 1

#define DISPLAY_WIDTH 400
#define DISPLAY_HEIGHT 240


class View {
private:
  bool visable = true;
public:
  virtual void render(Adafruit_SharpMem& display)=0;
  virtual void control_handler(uint8_t code);
  virtual void character_handler(uint8_t code);
  bool isVisible() const;
};

class TextView: public View {
private:
  uint8_t x,y,size,color;
  String s;
public:
  TextView(uint8_t x, uint8_t y, String s, uint8_t size=2, uint8_t color=0);
  void render(Adafruit_SharpMem& display);
  void setString(String s);
  void getSize(Adafruit_SharpMem& display,int16_t &x1,int16_t &y1, uint16_t &w,uint16_t &h) const;
};

class NavView: public View {
private:
  TextView battery,time;
public:
  NavView(String battery,String time);
  void render(Adafruit_SharpMem& display);
  void setBattery(String battery_string);
  void setTime(String time_string);
  // void control_handler(uint8_t code);
  // void character_handler(uint8_t code);
};


#endif
