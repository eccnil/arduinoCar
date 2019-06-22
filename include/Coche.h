#ifndef _COCHE_H_
#define _COCHE_H_

#include "Wheel.h"

class Coche {
    // maxima diferencia de potencia en las ruedas de cada lado
    static const int maxDeltaGiro = 60;
    int velocidad = 0;
    int giro = 0;
    void actualizaRuedas();
public:
    Wheel *ruedaIzq ;
    Wheel *ruedaDer ;
    Coche(Wheel *izq, Wheel *der) {
        ruedaIzq = izq;
        ruedaDer = der;
    }
    void init(){
        ruedaIzq->init();
        ruedaDer->init();
        Serial.println("init coche");
    }
    void setVelocidad(int porcentaje){
        if (porcentaje != velocidad){
            velocidad = porcentaje;
            actualizaRuedas();
        }
    }
    void setGiro(int porcentajeDerecha){
            if (porcentajeDerecha != giro){
            giro = porcentajeDerecha;
            actualizaRuedas();
        }
    }
};

void Coche::actualizaRuedas(){
    int d,i;

    int delta = map (giro , -100 , 100 , - maxDeltaGiro / 2 ,  maxDeltaGiro / 2);

    d = velocidad + delta;
    i = velocidad - delta;

    if (d>100) {i -= d-100; d = 100;}
    if (i>100) {d -= i-100; i = 100;}
    if (d< -100) {i += d - -100; d = -100;}
    if (i< -100) {d += i - -100; i = -100;}
    Serial.println("potencia a los motores");
    Serial.println(d);
    Serial.println(i);
    ruedaDer->move(d);
    ruedaIzq->move(i);
}

#endif