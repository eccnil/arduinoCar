#include <Arduino.h>
#include "WheelESP32.h"


#define PIN_MOTOR_A_POW 16
#define PIN_MOTOR_A_DIR 4
#define PWM_CHANNEL_MOTOR_A 0

Wheel rueda(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR, PWM_CHANNEL_MOTOR_A);


void setup(){
    Serial.begin(115200);
    Serial.println("Car initiating");
    rueda.init();
}
 
void loop(){  
    Serial.println("looping");
    int time = 3000; 
    delay(time);
    rueda.move(30);
    delay(time);
    rueda.move(60);
    delay(time);
    rueda.move(80);
    delay(time);
    rueda.move(100);
    delay(time);
    rueda.move(50);
    delay(time);
    rueda.move(80);
    delay(time);
    rueda.move(0);
    delay(time);
    rueda.move(-50);
    delay(time);
    rueda.move(-100);
    delay(time);
    rueda.move(-20);
    delay(time);
    rueda.move(0);
    delay(time);
}

