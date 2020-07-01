#ifndef _analog_sensor_hpp_
#define _analog_sensor_hpp_

#include <Arduino.h>

class AnalogSensor {
  private:
    int analogPin;
  public:
    AnalogSensor(int dataPin) {
      analogPin=dataPin;
    }
    int read(int samples=3){
      int reads=0;
      for (int i = samples ; i; i--){
        reads += analogRead(analogPin);
      }
      return reads/samples;
    }
};
#endif