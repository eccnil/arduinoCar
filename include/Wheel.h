#ifndef _WHEEL_H_
#define _WHEEL_H_

#include <Arduino.h>


class  Wheel {
  int pinPow;
  int pintDir;
  static const int MIN_INPUT = 75; //min value that produces movement (adjust it)
public:
  Wheel(int PIN_POW, int PIN_DIR){
    pinPow=PIN_POW;
    pintDir=PIN_DIR;
  }
  void init (){
    pinMode(pinPow, OUTPUT);
    pinMode(pintDir, OUTPUT);
  }
  //speed range (-100, 100)
  void move (int speedPercent ){
    int pmwInput ;
    if (speedPercent == 0){
      pmwInput = 0;
    } else if (speedPercent < 0){
      pmwInput = map(abs(speedPercent), 0,100, MIN_INPUT,255);
    } else{ 
      pmwInput = map(abs(speedPercent), 0,100, 255-MIN_INPUT, 0);
    }auto direccion = speedPercent > 0 ? HIGH :  LOW;
    move (pmwInput, direccion);
  }
  //speed range (0, 255) y (HIG | LOW)
  void move (int pmwInput, int direccion ){
    Serial.print("-- ");Serial.print(pmwInput);Serial.print(" : ");Serial.println(direccion);
    analogWrite(pinPow,pmwInput);
    digitalWrite(pintDir,direccion);
  }
};

#endif