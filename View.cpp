#include "View.h"

void View::control_handler(uint8_t code){
  return;
}
void View::character_handler(uint8_t code){
  return;
}
bool View::isVisible() const{
  return visable;
}
TextView::TextView(uint8_t x, uint8_t y,String s, uint8_t size, uint8_t color){
  this->x = x;
  this->y = y;
  this->size = size;
  this->color = color;
  this->s = s;
}
void TextView::setString(String s){
  this->s = s;
}
void TextView::getSize(Adafruit_SharpMem& display,int16_t &x1,int16_t &y1, uint16_t &w,uint16_t &h) const{
  display.getTextBounds(s, x, y, &x1, &y1, &w, &h);
}
void TextView::render(Adafruit_SharpMem& display){
  display.setRotation(0);
  display.setTextSize(size);
  if(color == 0){
    display.setTextColor(BLACK);
  } else {
    display.setTextColor(WHITE, BLACK);
  }
  display.setCursor(x,y);
  display.println(s);
}

NavView::NavView(String battery_string, String time_string)
  :battery(5,5,battery_string,2,1),time(0,5,time_string,2,1) {

}
void NavView::render(Adafruit_SharpMem& display){

}
void NavView::setBattery(String battery_string){
}
void NavView::setTime(String time_string){
}
