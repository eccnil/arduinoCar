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
    void setOnClick(ButtonEvent f) {button.onClick = f;}
    void setOnLongClick(ButtonEvent f) {button.onLongClick = f;}
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
    return xSensor.read(7);
}

int Joystick::getY(){
    return ySensor.read(7);
}

Joystick::~Joystick()
{
}


#endif