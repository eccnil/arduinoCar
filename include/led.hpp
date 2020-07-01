#ifndef _led_hpp_
#define _led_hpp_

#include <Arduino.h>
class Led {
  private:
    int pin;
    bool activeHigh;
  public:
    Led(int pin, bool activeHighLevel=true){
      this->pin = pin;
      this->activeHigh = activeHighLevel;
      pinMode(pin, OUTPUT);
    }
    void update(bool status){
      /*
      status                   false   true
      active Highlevel true    low     high
      active highlevel false   high    low
      */
      int level = (status != activeHigh)? LOW : HIGH;
      digitalWrite(this->pin, level);
    }
};

#endif