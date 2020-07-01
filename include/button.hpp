#ifndef _BUTTON_H_
#define _BUTTON_H_
#include <functional>
//#define debug 1

typedef std::function<void()> ButtonEvent; //took from http://tedfelix.com/software/c++-callbacks.html

enum ButtonStatus {idle, debouncingPressed, pressed, longPressed, debouncingIdle};

class Button {
    char gpioPin;
    int longClick=2000;
    int debounceTimeMilis=180;
    unsigned long statusTimestamp=0;
    ButtonStatus status = idle;
public:
    Button(char gpioPin);
    void init();
    void stop();
    void timer(unsigned long ms);
    ButtonEvent onClick;
    ButtonEvent onLongClick; 
};

#endif