#include <Arduino.h>
#include "common_esp_now.h"
#include <Arduino.h>
#include "WheelESP32.h"
#include "Coche.h"
#include <NewPing.h> //sonar
#include "tacometer.h"

#define PIN_MOTOR_A_POW 25
#define PIN_MOTOR_A_DIR 26
#define PWM_CHANNEL_MOTOR_A 0
#define PIN_MOTOR_B_POW 33
#define PIN_MOTOR_B_DIR 32
#define PWM_CHANNEL_MOTOR_B 1
#define SONAR_ECHO_PIN 15
#define SONAR_TRIGGER_PIN 2
#define SONAR_DISTANCE 200
#define PIN_TACOMETRO_A 4
#define PIN_TACOMETRO_B 5

unsigned int centerX = 0xFFFF; 
unsigned int centerY = 0xFFFF;

struct_message remoteCommand;
Wheel ruedaDer(PIN_MOTOR_B_POW, PIN_MOTOR_B_DIR, PWM_CHANNEL_MOTOR_B);
Wheel ruedaIzq(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR, PWM_CHANNEL_MOTOR_A);
Coche coche(&ruedaIzq, &ruedaDer);
NewPing ojos(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_DISTANCE);
volatile tacometerInterruptionStruct tacometroISR_A;
Tacometer tacometroIzq(PIN_TACOMETRO_A,  & tacometroISR_A , 200, 20);
void ISR_A () { tacometerISRHandler(tacometroIzq); }
int distanciaFrente = 0;

int corregirVelocidad(int);
int corregirGiro(int);
void drive(int x, int y, bool e);

// callback function that will be executed when data is received from 'mando'
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&remoteCommand, incomingData, sizeof(remoteCommand));
}



void setup(){
    Serial.begin(115200);
    Serial.println("Car initiating");
    coche.init();
 
    Serial.println("tacometers initiating");
    attachInterrupt(digitalPinToInterrupt(PIN_TACOMETRO_A), ISR_A, FALLING);


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
    //if button is pressed calibrate center position of joistick
    if (remoteCommand.e) {
        centerX = remoteCommand.x;
        centerY = remoteCommand.y;
    }
    //do drive
    drive(remoteCommand.x, remoteCommand.y, remoteCommand.e);
    yield();
    //TODO: mover a otro hilo
    distanciaFrente = ojos.ping_cm();
    //TODO: llamar a drive desde aqui en vez de desde el mando o el radár no frenará
}

void drive(int x, int y, bool e){
    int acelerador, volante;
    int velocidad = 0; 
    int giro = 0;

    //calcular las posiciones del acelerador y volante
    acelerador =  map(x,0,centerX*2,-100,100);
    volante = map(y,0,centerY*2,100,-100);

    //aplicar logica a las intenciones
    velocidad = corregirVelocidad(acelerador);
    giro = corregirGiro(volante);

    //actuar sobre los motores
    coche.setGiro(giro);
    coche.setVelocidad(velocidad);

     // depuración
    //Serial.print("x_mando ");
    //Serial.print(x);
    //Serial.print(" y_mando ");
    //Serial.print(y);
    //Serial.print(e);
    //Serial.print(" acelerador_mando ");
    //Serial.print(acelerador);
    //Serial.print(" volante_mando ");
    //Serial.print(volante);
    //Serial.print(" distancia ");
    //Serial.print(distanciaFrente);
    Serial.print(" velocidad_motores: ");
    Serial.print(velocidad);
    Serial.print(" giro_motores: ");
    Serial.print(giro);
    Serial.print(" motor_der ");
    Serial.print(coche.ruedaDer->getCurrentPow());
    Serial.print(" motor_Izq ");
    Serial.print(coche.ruedaIzq->getCurrentPow());
    Serial.println();
}

int corregirVelocidad( int v){
    if (v>100) v=100;
    if (v< -100) v=-100;
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
    if (v>100) v=100;
    if (v< -100) v=-100;
    if (v >-2 && v <2) v = 0; //deadzone
    return v;
}