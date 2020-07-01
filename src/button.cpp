#include "button.hpp"
#include <arduino.h>
#include <functional>

Button::Button(char gpioPin){
    this->gpioPin = gpioPin;
}

void Button::init(){
    pinMode(gpioPin, INPUT_PULLUP);
    std::function<void()> myint = [](){ return;};
}

void Button::timer(unsigned long ms){
    bool buttonPressedRead = digitalRead(gpioPin) == LOW;
    bool statusDebounced = ms > statusTimestamp + debounceTimeMilis;
    
    switch (status){
    case ButtonStatus::idle:
        if (buttonPressedRead){
            status = debouncingPressed;
            statusTimestamp = ms;
        }
        break;
    case ButtonStatus::debouncingPressed:
        if (statusDebounced){
            status = pressed;
        }
        break;
    case ButtonStatus::pressed:
        if (ms > statusTimestamp + longClick){
            status = longPressed;
            #ifdef debug
            Serial.println("[Button] long click!!");
            #endif
            if(onLongClick != NULL ) onLongClick();
        } else if (!buttonPressedRead){
            status = debouncingIdle;
            statusTimestamp = ms;
            #ifdef debug
            Serial.println("[Button] clicked!"); 
            #endif
            if(onClick != NULL) onClick();
        }
        break;
    case ButtonStatus::longPressed:
        if (!buttonPressedRead){
            status = debouncingIdle;
            statusTimestamp = ms;
            #ifdef debug
            Serial.println("[Button] released"); 
            #endif 
        }
        break;
    case ButtonStatus::debouncingIdle:
        if (statusDebounced){
            status = idle;
        }
        break;
    }

}