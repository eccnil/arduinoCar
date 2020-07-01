#ifndef _rgbled_hpp_
#define _rgbled_hpp_

#include "led.hpp"

class RGBLed{
    protected:
        Led ledRed;
        Led ledGreen;
        Led ledBlue;
    public:
        RGBLed(int redPin, int greenPin, int bluePin, bool activeHighLevel = true):
            ledRed(redPin,activeHighLevel),
            ledGreen(greenPin, activeHighLevel),
            ledBlue(bluePin,activeHighLevel)
        {
        }
        void update (bool redf, bool greenf, bool bluef){
            ledRed.update(redf);
            ledGreen.update(greenf);
            ledBlue.update(bluef);
        }
        void setOff() {update(0,0,0);}
        void setWhite() {update(1,1,1);}
        void setRed() {update(1,0,0);}
        void setGreen() {update (0,1,0);}
        void setBlue() {update(0,0,1);}
        void setYellow() {update (1,1,0);}
        void setCyan() {update (0,1,1);}
        void setMagenta() {update (1,0,1);}

};

#endif