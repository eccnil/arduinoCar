#include <Arduino.h>
#include "Wheel.h"
#include <Servo.h>
#include "Coche.h"
#include <NewPing.h> //sonar
#include "Radar.h"
#include <PSX.h>

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
#define PIN_MANDO_DATA 2
#define PIN_MANDO_CMD 3
#define PIN_MANDO_ATTENTION 4
#define PIN_MANDO_CLOCK 12
#define MANDO_DELAY 10 //Este numero no se para que es

Wheel ruedaIzq(PIN_MOTOR_B_POW, PIN_MOTOR_B_DIR);
Wheel ruedaDer(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR);
Coche coche(&ruedaIzq, &ruedaDer);
Servo cuello;
NewPing ojos(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_DISTANCE);
Radar vigilante(&cuello, &ojos);
//setupPins(byte dataPin, byte cmndPin, byte attPin, byte clockPin, byte delay);
PSX mando; // Creamos la clase del mando PS2
PSX::PSXDATA lecturaMando;

int distanciaFrente,distanciaIzquierda,distanciaDerecha = 0;

void setup() {
  Serial.begin(9600);
  coche.init();
  cuello.attach(PIN_CUELLO, CUELLO_MIN, CUELLO_MAX);
  vigilante.agregarAngulo(90, &distanciaFrente);
  vigilante.agregarAngulo(60, &distanciaDerecha);
  vigilante.agregarAngulo(120, &distanciaIzquierda);
  mando.setupPins(PIN_MANDO_DATA, PIN_MANDO_CMD, PIN_MANDO_ATTENTION, PIN_MANDO_CLOCK, MANDO_DELAY);
  mando.config(PSXMODE_ANALOG);
}

const size_t USHORT_BIT = 8 * sizeof(byte);

byte ConvertMsbFirstToLsbFirst(const byte input) {
  byte output = 0;
  for (size_t offset = 0; offset < USHORT_BIT; ++offset) {
    output |= ((input >> offset) & 1) << (USHORT_BIT - 1 - offset);
  }
  return output;
}

void loop() {
  int acelerador, volante;
  int velocidad;
  vigilante.loop();
  coche.setGiro(0);
  velocidad  = 100;

//leer velocidad del mando a distancia
  int errorEnMnado = mando.read(lecturaMando);
  if(errorEnMnado == PSXERROR_SUCCESS){
    acelerador = 255-ConvertMsbFirstToLsbFirst(lecturaMando.JoyLeftY);
    volante = ConvertMsbFirstToLsbFirst(lecturaMando.JoyRightX);
    Serial.print(" ** mando: acelerador ");
    Serial.print(acelerador);
    Serial.print("   volante ");
    Serial.print(volante);
    Serial.print(" ** ");
  }

//haemos que los sensores nos frenen si vamos a chocar
  bool nadacerca = distanciaFrente == 0 || distanciaFrente > 25;
   nadacerca = nadacerca && (distanciaDerecha == 0 || distanciaDerecha > 20);
   nadacerca = nadacerca && (distanciaIzquierda == 0 || distanciaIzquierda > 20); 
  if(nadacerca){
    coche.setVelocidad(velocidad);
  } else {
    coche.setVelocidad(0);
    Serial.print("para!");
  }


  
  Serial.print(" <");
  Serial.print(distanciaIzquierda);
  Serial.print(" ^");
  Serial.print(distanciaFrente);
  Serial.print(" >");
  Serial.print(distanciaDerecha);
  Serial.println();
}