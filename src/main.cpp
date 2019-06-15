#include <Arduino.h>
#include "Wheel.h"
#include "Servo.h"


#define PIN_MOTOR_A_POW 9
#define PIN_MOTOR_A_DIR 8
#define PIN_MOTOR_B_POW 6
#define PIN_MOTOR_B_DIR 7

#define DIRECCION_I2C_CUELLO 0x42


Wheel ruedaIzq(PIN_MOTOR_B_POW, PIN_MOTOR_B_DIR);
Wheel ruedaDer(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR);
Servo cuello(DIRECCION_I2C_CUELLO);

void setup() {
  ruedaIzq.init();
  ruedaDer.init();
  cuello.init();
}

void loop() {
  ruedaIzq.move(700,true);
  ruedaDer.move(600,false);
  cuello.move(128);
  delay(2000);
  ruedaIzq.move(1000,true);
  ruedaDer.move(1000,true);
  cuello.move(255);
  delay(2000);
  ruedaIzq.move(700,false);
  ruedaDer.move(0,true);
  cuello.move(1);
  delay(2000);
}