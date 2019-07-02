#include <Arduino.h>
#include "Wheel.h"
#include <Servo.h>
#include "Coche.h"
#include <NewPing.h> //sonar
#include "Radar.h"

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
Radar vigilante(&cuello, &ojos);
int distanciaFrente,distanciaIzquierda,distanciaDerecha = 0;

void setup() {
  Serial.begin(9600);
  coche.init();
  cuello.attach(PIN_CUELLO, CUELLO_MIN, CUELLO_MAX);
  vigilante.agregarAngulo(90, &distanciaFrente);
  vigilante.agregarAngulo(60, &distanciaDerecha);
  vigilante.agregarAngulo(120, &distanciaIzquierda);
}


void loop() {
  vigilante.loop();
  Serial.print(" <");
  Serial.print(distanciaIzquierda);
  Serial.print(" ^");
  Serial.print(distanciaFrente);
  Serial.print(" >");
  Serial.print(distanciaDerecha);
  Serial.println();
}