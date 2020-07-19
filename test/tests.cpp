#include <Arduino.h>
#define TESTTACOMETER

#define PIN_MOTOR_A_POW 25
#define PIN_MOTOR_A_DIR 26
#define PWM_CHANNEL_MOTOR_A 0
#define PIN_MOTOR_B_POW 33
#define PIN_MOTOR_B_DIR 32
#define PWM_CHANNEL_MOTOR_B 1
#define SONAR_ECHO_PIN 15
#define SONAR_TRIGGER_PIN 2
#define SONAR_DISTANCE 200

#ifdef TESTWHEEL
    #include "WheelESP32.h"
    Wheel rueda(PIN_MOTOR_A_POW, PIN_MOTOR_A_DIR, PWM_CHANNEL_MOTOR_A);
    void testSetup(){
            rueda.init();
    }
    void testLoop(){
        Serial.println("looping");
        int time = 3000; 
        delay(time);
        rueda.move(30);
        delay(time);
        rueda.move(60);
        delay(time);
        rueda.move(80);
        delay(time);
        rueda.move(100);
        delay(time);
        rueda.move(50);
        delay(time);
        rueda.move(80);
        delay(time);
        rueda.move(0);
        delay(time);
        rueda.move(-50);
        delay(time);
        rueda.move(-100);
        delay(time);
        rueda.move(-20);
        delay(time);
        rueda.move(0);
        delay(time);
    }
#endif

#ifdef TESTSONAR
    #include <NewPing.h> //sonar
    NewPing ojos(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN, SONAR_DISTANCE);

    void testSetup(){
    }
    void testLoop(){
         auto dst = ojos.ping_cm();
        int time = 2000; 
        Serial.println(dst);
        delay(time);
    }
#endif

#ifdef TESTTACOMETER
    #include "tacometer.h"
    #define PIN_TACOMETRO_A 4

    volatile int counter = 0;

    volatile tacometerInterruptionStruct tacometroISR_A;
    Tacometer tacometroIzq(PIN_TACOMETRO_A,  & tacometroISR_A , 200, 20);
    void ISR_A () { counter++ ; tacometerISRHandler(tacometroIzq); }

    void testSetup(){
        attachInterrupt(digitalPinToInterrupt(PIN_TACOMETRO_A), ISR_A, FALLING);
    }
    void testLoop(){
        delay(20);
        long period = tacometroISR_A.period;
        //Serial.print(counter);
        //Serial.print(" ");
        //Serial.print(period);
        //Serial.print(" ");
        //Serial.print(tacometroIzq.getPeriod());
        //Serial.print(" ");
        Serial.print(tacometroIzq.getRPMs());
        Serial.println();
    }
#endif




void setup(){
    Serial.begin(115200);
    Serial.println("test initiating");
    testSetup();
}
 
void loop(){  
    testLoop();
}

