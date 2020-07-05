#ifndef _WHEEL_32_H_
#define _WHEEL_32_H_

#include <Arduino.h>

// Setting PWM properties
const int freq = 3000;
const int pwmChannel = 0;
const int resolution = 8;

class  Wheel {
  int pinPow;
  int pintDir;
  static const int MIN_INPUT = 75; //min value that produces movement (adjust it)
  int channel;
public:
  Wheel(int PIN_POW, int PIN_DIR, int channel=0){
    pinPow=PIN_POW;
    pintDir=PIN_DIR;
    this->channel = channel;
  }
  void init (){
    ledcSetup(channel,freq, resolution);
    ledcAttachPin(pinPow, channel);
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
    //Serial.print("-- ");Serial.print(pmwInput);Serial.print(" : ");Serial.println(direccion);
    ledcWrite(channel,pmwInput);
    digitalWrite(pintDir,direccion);
  }
};

#endif