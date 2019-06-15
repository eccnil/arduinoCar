
#include <Arduino.h>


class  Wheel {
  int pinPow;
  int pintDir;
public:
  Wheel(int PIN_POW, int PIN_DIR){
    pinPow=PIN_POW;
    pintDir=PIN_DIR;
  }
  void init (){
    pinMode(pinPow, OUTPUT);
    pinMode(pintDir, OUTPUT);
  }
  //speed range 0-1024
  void move (int speed, bool fwd){
    analogWrite(pinPow,speed / 4);
    digitalWrite(pintDir,fwd?HIGH:LOW);
  }
};