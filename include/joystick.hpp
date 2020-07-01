#ifndef _joystick_hpp_
#define _joystick_hpp_

#include "button.hpp"
#include "analog_sensor.hpp"

class Joystick
{
protected:
    AnalogSensor xSensor;
    AnalogSensor ySensor;
    Button button;
public:
    Joystick(char pinX, char pinY, char pinButton);
    ~Joystick();
    void setup();
    void loop();
    int getX();
    int getY();
    bool getBtn();
};

Joystick::Joystick(char pinX, char pinY, char pinButton):
xSensor(pinX), ySensor(pinY), button(pinButton)
{
}

void Joystick::setup (){
    button.init();
}

void Joystick::loop(){
    unsigned long time = millis();
    button.timer(time);
}

int Joystick::getX(){
    return xSensor.read();
}

int Joystick::getY(){
    return ySensor.read();
}
bool Joystick::getBtn(){
    //TODO: retrun button
    return false;
}

Joystick::~Joystick()
{
}


#endif