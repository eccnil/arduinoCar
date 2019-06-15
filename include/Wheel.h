
#include <Arduino.h>


class  Wheel {
  int pinPow;
  int pintDir;
  static const int MIN_INPUT = 50; //min value that produces movement (adjust it)
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
    int pmwInput = map(abs(speedPercent),0,MIN_INPUT,100,255);
    auto direccion = speedPercent > 0 ? HIGH :  LOW;
    analogWrite(pinPow,pmwInput);
    digitalWrite(pintDir,direccion);
  }
};