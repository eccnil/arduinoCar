#include <Arduino.h>
#include "Wheel.h"
#include "Servo.h"


#define PIN_MOTOR_L_POW 6
#define PIN_MOTOR_L_DIR 7
#define PIN_MOTOR_D_POW 11
#define PIN_MOTOR_D_DIR 12

#define DIRECCION_I2C_CUELLO 0x42


Wheel ruedaIzq(PIN_MOTOR_L_POW, PIN_MOTOR_L_DIR);
Wheel ruedaDer(PIN_MOTOR_D_POW, PIN_MOTOR_D_DIR);
Servo cuello(DIRECCION_I2C_CUELLO);

void setup() {
  ruedaIzq.init();
  ruedaDer.init();
  cuello.init();
}

void loop() {
  ruedaIzq.move(700,true);
  ruedaDer.move(700,false);
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