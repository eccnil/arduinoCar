#ifndef _SERVO_H_
#define _SERVO_H_
#include <Wire.h>

class Servo
{
private:
    /* data */
    int direccion;
public:
    Servo(int direccion);
    ~Servo();
    void init();
    //0 - 256
    void move(uint8_t angulo);
};

Servo::Servo(int direccion)
{
    this->direccion = direccion;
}

Servo::~Servo()
{
}

void Servo::init(){
    Wire.begin();
}

void  Servo::move (uint8_t angulo){
    Wire.beginTransmission(direccion); 
    Wire.write(angulo);        // sends five bytes
    Wire.endTransmission(); 
}

#endif