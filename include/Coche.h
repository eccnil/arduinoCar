#ifndef _COCHE_H_
#define _COCHE_H_

#include "Wheel.h"

class Coche {
    // maxima diferencia de potencia en las ruedas de cada lado
    static const int maxDeltaGiro = 80;
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
    int delta = map (giro , -100 , 100 , - maxDeltaGiro / 2 ,  maxDeltaGiro / 2);
    int d = velocidad + delta;
    int i = velocidad - delta;

    if (d > 100) { i -= d-100; d = 100; }
    if (i > 100) { d -= i-100; i = 100; }
    if (d < -100) { i -= d - -100; d = -100; }
    if (i < -100) { d -= i - -100; i = -100; }

    Serial.print("potencia a los motores: " );Serial.print(d);Serial.print(" , ");Serial.println(i);
    ruedaDer->move(d);
    ruedaIzq->move(i);
}

#endif