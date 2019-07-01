#include <Arduino.h>
#include "Wheel.h"
#include <Servo.h>
#include "Coche.h"

#define PIN_MOTOR_A_POW 9
#define PIN_MOTOR_A_DIR 8
#define PIN_MOTOR_B_POW 6
#define PIN_MOTOR_B_DIR 7
#define PIN_CUELLO 5
#define CUELLO_MAX 2580
#define CUELLO_MIN 580

Wheel ruedaIzq(PIN_MOTOR_B_POW, PIN_MOTOR_B_DIR);
Wheel ruedaDer(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR);
Coche coche(&ruedaIzq, &ruedaDer);
Servo cuello;

void setup() {
  Serial.begin(9600);
  coche.init();
  cuello.attach(PIN_CUELLO, CUELLO_MIN, CUELLO_MAX);
}

void loop() {
  coche.setVelocidad(100);
  coche.setGiro(50);
  cuello.write(0);
  delay(4000);
  coche.setVelocidad(-100);
  coche.setGiro(50);
  cuello.write(90);
  delay(2000);
  coche.setVelocidad(100);
  coche.setGiro(0);
  cuello.write(0);
  delay(4000);
  coche.setVelocidad(-100);
  coche.setGiro(0);
  cuello.write(90);
  delay(2000);
  coche.setVelocidad(0);
  coche.setGiro(-100);
  cuello.write(180);
  delay(2000);
}