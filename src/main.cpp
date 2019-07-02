#include <Arduino.h>
#include "Wheel.h"
#include <Servo.h>
#include "Coche.h"
#include <NewPing.h> //sonar

#define PIN_MOTOR_A_POW 9
#define PIN_MOTOR_A_DIR 8
#define PIN_MOTOR_B_POW 6
#define PIN_MOTOR_B_DIR 7
#define PIN_CUELLO 5
#define CUELLO_MAX 2580
#define CUELLO_MIN 580
#define SONAR_ECHO_PIN 10
#define SONAR_TRIGGER_PIN 11
#define SONAR_DISTANCE 200

Wheel ruedaIzq(PIN_MOTOR_B_POW, PIN_MOTOR_B_DIR);
Wheel ruedaDer(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR);
Coche coche(&ruedaIzq, &ruedaDer);
Servo cuello;
NewPing ojos(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_DISTANCE);

void setup() {
  Serial.begin(9600);
  coche.init();
  cuello.attach(PIN_CUELLO, CUELLO_MIN, CUELLO_MAX);

}

int mira(int angulo, String texto){
  int distance = 0;
  cuello.write(angulo);
  delay(200);
  distance = ojos.ping_cm();
  Serial.print (texto);
  Serial.println (distance);
  return distance;
}

void loop() {
  coche.setVelocidad(100);
  coche.setGiro(50);
  mira(0, "derecha ");
  delay(2000);
  coche.setVelocidad(-100);
  coche.setGiro(50);
  mira(90, "frente ");
  delay(2000);
  coche.setVelocidad(100);
  coche.setGiro(0);
  mira(180, "izquierda ");
  delay(2000);
  coche.setVelocidad(-100);
  coche.setGiro(0);
  mira(90, "frente ");
  delay(2000);
  coche.setVelocidad(0);
  coche.setGiro(-100);
  cuello.write(180);
  mira(90, "frente ");
  delay(2000);
}