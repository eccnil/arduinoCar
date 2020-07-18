#include <Arduino.h>
#include "common_esp_now.h"
#include <Arduino.h>
#include "WheelESP32.h"
#include "Coche.h"
#include <NewPing.h> //sonar

#define PIN_MOTOR_A_POW 25
#define PIN_MOTOR_A_DIR 26
#define PWM_CHANNEL_MOTOR_A 0
#define PIN_MOTOR_B_POW 33
#define PIN_MOTOR_B_DIR 32
#define PWM_CHANNEL_MOTOR_B 1
#define SONAR_ECHO_PIN 16
#define SONAR_TRIGGER_PIN 2
#define SONAR_DISTANCE 200

#define rawXZero 2660
#define rawYZero 2657

struct_message remoteCommand;
Wheel ruedaDer(PIN_MOTOR_B_POW, PIN_MOTOR_B_DIR, PWM_CHANNEL_MOTOR_B);
Wheel ruedaIzq(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR, PWM_CHANNEL_MOTOR_A);
Coche coche(&ruedaIzq, &ruedaDer);
NewPing ojos(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_DISTANCE);
int distanciaFrente = 0;

int corregirVelocidad(int);
int corregirGiro(int);
void drive(int x, int y);

// callback function that will be executed when data is received from 'mando'
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&remoteCommand, incomingData, sizeof(remoteCommand));
}

void setup(){
    Serial.begin(115200);
    Serial.println("Car initiating");
    coche.init();
    Serial.println("Radio initiating");


    //Initialize ESP-NOW;
    //You must initialize Wi-Fi before initializing ESP-NOW.
#ifdef ESP8266
    WiFi.mode(WIFI_STA); // MUST NOT BE WIFI_MODE_NULL
#elif ESP32
    WiFi.mode(WIFI_MODE_STA);
#endif
    if (esp_now_init() != ESP_OK) { //Initializes ESP-NOW. 
        Serial.println("Error initializing ESP-NOW");
        return;
    } 

    //Register for a receive callback function (OnDataRecv). This is a function that will be executed when a message is received.
    esp_now_register_recv_cb(OnDataRecv);
    Serial.println("Car ready");

}
 
void loop(){   
    drive(remoteCommand.x, remoteCommand.y);
    yield();
    //TODO: mover a otro hilo
    //distanciaFrente = ojos.ping_cm();
    //TODO: llamar a drive desde aqui en vez de desde el mando o el radár no frenará
}

void drive(int x, int y){
    int acelerador, volante;
    int velocidad = 0; 
    int giro = 0;

    //calcular las posiciones del acelerador y volante
    acelerador = x>rawXZero ? map(x,rawXZero+1,0xFFF,0,100): map(x,0,rawXZero,-100,0);
    volante = y>rawYZero ? map(y,rawYZero+1,0xFFF,0,100): map(y,0,rawYZero,-100,0);

    //aplicar logica a las intenciones
    velocidad = corregirVelocidad(acelerador);
    giro = corregirGiro(volante);

    //actuar sobre los motores
    coche.setGiro(giro);
    coche.setVelocidad(velocidad);

     // depuración
    Serial.print("xy mando");
    Serial.print(x);
    Serial.print(',');
    Serial.print(y);
    Serial.print(" -");
    Serial.print(" ** mando: acelerador ");
    Serial.print(acelerador);
    Serial.print(" volante ");
    Serial.print(volante);
    Serial.print(" ** sensor: ");
    Serial.print(distanciaFrente);
    Serial.print(" ** motores: velocidad: ");
    Serial.print(velocidad);
    Serial.print(" giro: ");
    Serial.print(giro);
    Serial.println();
}

int corregirVelocidad( int v){
    int result = v;
    //haemos que los sensores nos frenen si vamos a chocar
    bool nadacerca = distanciaFrente == 0 || distanciaFrente > 25; 
    if(nadacerca || v <0 ){
        //sesgo por el mando que tenemos (zona muerta)
        if(result < 5 && result > -5 ) {
            result = 0;
        } else {
            result = v;
        }
    } else {
        result = 0;
        Serial.print("para!");
    }
    return result;
}

int corregirGiro(int v){
    if (v >-2 && v <2) v = 0; //deadzone
    return v;
}