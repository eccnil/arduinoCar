#ifndef _SERVO_H_
#define _SERVO_H_
#include <Wire.h>

class Servo
{
private:
    int direccion;
public:
    Servo(int direccion) { 
        this->direccion = direccion;
    }
    ~Servo() {}
    void init() {
        Wire.begin();
    }
    //0 - 256
    void move(uint8_t angulo) {
        Wire.beginTransmission(direccion); 
        Wire.write(angulo);        // sends five bytes
        Wire.endTransmission(); 
    }
};

#endif