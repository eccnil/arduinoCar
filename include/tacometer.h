#ifndef _tacometer_h_
#define _tacometer_h_
#include <Arduino.h>

struct tacometerInterruptionStruct
{
    int64_t lastTickMicroSeconds = 0 ;
    int64_t period = -1 ;
};

class Tacometer
{
private:
    int pin;
    volatile tacometerInterruptionStruct * reads;
    int64_t maxPeriodMicros;
    int ticksPerRev;
public:
    Tacometer(int tacometerPin, volatile tacometerInterruptionStruct * interrupData, int maxPeriodMillis = 1000, int ticksPerRev = 1);
    friend inline void tacometerISRHandler (Tacometer tacometer);
    long getPeriod();
    double getRPMs();
    ~Tacometer();
};

//call this function from your isr
inline void tacometerISRHandler (Tacometer tacometer)
{
    int64_t currentTime = esp_timer_get_time();
    tacometer.reads->period = currentTime - tacometer.reads->lastTickMicroSeconds;
    tacometer.reads->lastTickMicroSeconds = currentTime;
}

Tacometer::Tacometer(int tacometerPin, volatile tacometerInterruptionStruct * interrupData,  int maxPeriodMilis, int ticksPerRev)
{
    pin = tacometerPin;
    reads = interrupData;
    this->ticksPerRev = ticksPerRev;
    this->maxPeriodMicros = 1000L * maxPeriodMilis;
}

// returns -1 if speed = 0 or no initialised
long Tacometer::getPeriod()
{
    //fixing reads
    long interval = reads->period;
    long lastRead = reads->lastTickMicroSeconds;
    long currentTime = esp_timer_get_time();

    /*
    Serial.print ("----    --  ");
    Serial.print (lastRead);
    Serial.print (" ");
    Serial.print (currentTime);
    Serial.print (" ");
    Serial.print ((long)maxPeriodMicros);
    Serial.print (" ");
    Serial.print ((long)currentTime - lastRead);
    Serial.println();
    */
    if(lastRead == 0 )
        return -1; //no reads already
    if((currentTime - lastRead) > maxPeriodMicros )
        return -2; //no revs detected recently
    if(interval > maxPeriodMicros)
        return -3; //lax read over cap
    return interval; 
}

double Tacometer::getRPMs()
{
    long period = getPeriod();
    if(period <= 0)
    {
        return 0.0;
    } 
    else 
    {
        return (60e6) / (period * ticksPerRev);
    }
}

Tacometer::~Tacometer()
{
}


#endif