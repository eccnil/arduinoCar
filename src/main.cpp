#include <Arduino.h>
#include "Wheel.h"
#include <Servo.h>
#include "Coche.h"
#include <NewPing.h> //sonar
#include "Radar.h"
#include "Mando.h"

#define PIN_MOTOR_A_POW 9
#define PIN_MOTOR_A_DIR 8
#define PIN_MOTOR_B_POW 6
#define PIN_MOTOR_B_DIR 7
#define PIN_MANDO_DATA 2
#define PIN_MANDO_CMD 3
#define PIN_MANDO_ATTENTION 4
#define PIN_MANDO_CLOCK 12
#define PIN_CUELLO 5
#define CUELLO_MAX 2580
#define CUELLO_MIN 580
#define SONAR_ECHO_PIN 10
#define SONAR_TRIGGER_PIN 11
#define SONAR_DISTANCE 200

Wheel ruedaIzq(PIN_MOTOR_B_POW, PIN_MOTOR_B_DIR);
Wheel ruedaDer(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR);
Coche coche(&ruedaIzq, &ruedaDer);
Mando mando (PIN_MANDO_DATA, PIN_MANDO_CMD, PIN_MANDO_ATTENTION, PIN_MANDO_CLOCK);
Servo cuello;
NewPing ojos(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_DISTANCE);
Radar vigilante(&cuello, &ojos);
int distanciaFrente,distanciaIzquierda,distanciaDerecha = 0;

int corregirVelocidad(int);
int corregirGiro(int);

void setup() {
  Serial.begin(9600);
  coche.init();
  mando.init();
  cuello.attach(PIN_CUELLO, CUELLO_MIN, CUELLO_MAX);
  vigilante.agregarAngulo(90, &distanciaFrente);
  vigilante.agregarAngulo(60, &distanciaDerecha);
  vigilante.agregarAngulo(120, &distanciaIzquierda);
}

void loop() {
  int acelerador, volante;
  int velocidad = 0; 
  int giro = 0;

  vigilante.loop();
  mando.loop();

  //leer velocidad y giro del mando a distancia
  acelerador = mando.getJoistickIzquierdoY();
  volante = mando.getJoistickDerechoX();
  
  //aplicar logica a las intenciones
  velocidad = corregirVelocidad(acelerador);
  giro = corregirGiro(volante);

  coche.setGiro(giro);
  coche.setVelocidad(velocidad);

  // depuración
  
  Serial.print(" ** mando: acelerador ");
  Serial.print(acelerador);
  Serial.print(" volante ");
  Serial.print(volante);
  Serial.print(" ** sensor: ");
  Serial.print(" <");
  Serial.print(distanciaIzquierda);
  Serial.print(" ^");
  Serial.print(distanciaFrente);
  Serial.print(" >");
  Serial.print(distanciaDerecha);
  Serial.print(" ** motores: velocidad: ");
  Serial.print(velocidad);
  Serial.print(" giro: ");
  Serial.print(giro);
  
  Serial.println();
  
}

int corregirVelocidad( int v){
  //traducir 0-100 a -100 +100
  v = v*2 - 100;
  int result;
  //haemos que los sensores nos frenen si vamos a chocar
  bool nadacerca = distanciaFrente == 0 || distanciaFrente > 25;
   nadacerca = nadacerca && (distanciaDerecha == 0 || distanciaDerecha > 20);
   nadacerca = nadacerca && (distanciaIzquierda == 0 || distanciaIzquierda > 20); 
  if(nadacerca || v <0 ){
    result = v;
  } else {
    result = 0;
    Serial.print("para!");
  }
  //sesgo por el mando que tenemos (zona muerta)
  if(result < 5 && result > -5 ) result = 0;
  return result;
}

int corregirGiro(int v){
  v = 100 - v; //cambio de escala
  v = v*2 - 100;
  return v;
}