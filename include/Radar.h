#ifndef _RADAR_H_
#define _RADAR_H_

#include <Servo.h>
#include <NewPing.h>
#include <SimpleTimer.h>
#include <Vector.h>
#include <stdlib.h>

#define MAXANGLES 9
#define STOP_TIME 25
#define TIEMPO_MEDICION

struct PuntoVigilancia
{
    int angulo;
    int * distancia;
};

class Radar
{
private:
    Servo * cuello;
    NewPing * ojos;
    PuntoVigilancia storageArray[MAXANGLES];
    Vector <PuntoVigilancia> angulos;
    int puntoVigilanciaActual=0; 
    long calcularTiempoDeGiro(int angO, int ang1);
public:
    Radar(Servo * servo, NewPing * sonar);
    void agregarAngulo(const int angulo, int*distancia);
    void loop();
};

Radar::Radar(Servo * servo, NewPing * sonar)
{
    this->cuello = servo;
    this->ojos = sonar;
    angulos.setStorage(storageArray);
}

void Radar::agregarAngulo(const int angulo, int * distancia){
    PuntoVigilancia nuevo = {};
    nuevo.angulo = angulo;
    nuevo.distancia = distancia;
    angulos.push_back(nuevo);
}
    
void Radar::loop(){
    //TODO: hacer no-bloqueante
    //averiguar cual es el siguient angulo
    int siguientePuntoVigilancia = (puntoVigilanciaActual + 1) % angulos.size();
    //calcular tiempo para llegar
    int anguloOrigen = angulos[puntoVigilanciaActual].angulo;
    int anguloDestino = angulos[siguientePuntoVigilancia].angulo;
    long tiempoDeGiro = calcularTiempoDeGiro(anguloOrigen,anguloDestino);
    //ir al angulo
    cuello->write(anguloDestino);
    //esperar a llegar
    delay(tiempoDeGiro);
    //medir
    int distancia = this->ojos->ping_cm();
    //esperar medición
    //TODO:pingCM es bloqueante

    //guardar medida
    int* medida = this->angulos[siguientePuntoVigilancia].distancia;
    *medida = distancia;
    //modificar cosas para la vez siguiente
    puntoVigilanciaActual = siguientePuntoVigilancia;
}

long Radar::calcularTiempoDeGiro(int ang0, int ang1){
    long offset = abs(ang0 - ang1);
    long result = (offset * 5 / 3) + STOP_TIME;
    //TODO: calcular tiempo
    return result;
}

#endif