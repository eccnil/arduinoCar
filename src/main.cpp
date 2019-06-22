#include <Arduino.h>
#include "Wheel.h"
#include "Servo.h"
#include "Coche.h"

#define PIN_MOTOR_A_POW 9
#define PIN_MOTOR_A_DIR 8
#define PIN_MOTOR_B_POW 6
#define PIN_MOTOR_B_DIR 7

#define DIRECCION_I2C_CUELLO 0x40

Wheel ruedaIzq(PIN_MOTOR_B_POW, PIN_MOTOR_B_DIR);
Wheel ruedaDer(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR);
Coche coche(&ruedaIzq, &ruedaDer);
Servo cuello(DIRECCION_I2C_CUELLO);

void setup() {
  Serial.begin(9600);
  coche.init();
  cuello.init();
}

void loop() {
  coche.setVelocidad(100);
  coche.setGiro(50);
  delay(2000);
  coche.setVelocidad(-100);
  coche.setGiro(50);
  delay(2000);
  coche.setVelocidad(100);
  coche.setGiro(0);
  delay(2000);
  coche.setVelocidad(-100);
  coche.setGiro(0);
  delay(2000);
  coche.setVelocidad(0);
  coche.setGiro(-100);
  delay(2000);
}