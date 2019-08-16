#ifndef _coche_h_
#define _coche_h_

#include <PSX.h>
#include <Arduino.h>

#define MANDO_DELAY 10 

class Mando
{
private:
    PSX controlador;
    PSX::PSXDATA lectura;
    byte pinData, pinCmd, pinAttention, pinClock;
    bool anyRead = false;
public:
    Mando (byte pinData, byte pinCmd, byte pinAttention, byte pinClock);
    ~Mando () {}
    void init();
    bool loop();
    byte getJoistickIzquierdoX() {return getJoistick('x');}
    byte getJoistickIzquierdoY() {return getJoistick('y');}
    byte getJoistickDerechoX() {return getJoistick('X');}
    byte getJoistickDerechoY() {return getJoistick('Y');}
    PSX::PSXDATA getBottones(){return lectura;}
private:
    static const size_t USHORT_BIT = 8 * sizeof(byte);
    static byte ConvertMsbFirstToLsbFirst(const byte input);
    byte getJoistick(char eje);
    byte getJoistickRaw(char eje);
};

Mando::Mando (byte pinData, byte pinCmd, byte pinAttention, byte pinClock){
    this->pinData = pinData;
    this->pinCmd = pinCmd;
    this->pinAttention = pinAttention;
    this->pinClock = pinClock;
}
void Mando::init(){
    controlador.setupPins(pinData, pinCmd, pinAttention, pinClock, MANDO_DELAY);
    controlador.config(PSXMODE_ANALOG);
}

bool Mando::loop(){
    int errorEnMnado = controlador.read(lectura);
    bool success = errorEnMnado == PSXERROR_SUCCESS;
    anyRead |= success;
    return success;
}

//izq minuscula, der mayuscula
byte Mando::getJoistick(char eje){
    byte unscale;
    byte rawData; //datos directos del sensor
    byte read;
    byte scaled;

    if(anyRead){
        rawData = getJoistickRaw(eje);
        unscale = ( eje=='x' || eje == 'X' ) ? 0 : 255 ; //la escala del eje y está invertida, con esta variable la corregimos
        read = unscale-ConvertMsbFirstToLsbFirst(rawData);
        scaled = map(read,0,255,00,100);
        return scaled;
    }
    else{
        return 0;
    }
}

//izq minuscula, der mayuscula
byte Mando::getJoistickRaw(char eje){
    switch(eje){
        case 'x': return lectura.JoyLeftX; 
        case 'y': return lectura.JoyLeftY;
        case 'X': return lectura.JoyRightX;
        case 'Y': return lectura.JoyRightY;
    }
}

byte Mando::ConvertMsbFirstToLsbFirst(const byte input) {
  byte output = 0;
  for (size_t offset = 0; offset < USHORT_BIT; ++offset) {
    output |= ((input >> offset) & 1) << (USHORT_BIT - 1 - offset);
  }
  return output;
}

#endif