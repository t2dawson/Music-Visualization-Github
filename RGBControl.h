#ifndef __RGB_CONTROL__HEADER__
#define __RGB_CONTROL__HEADER__

#include "SerialLogger.h"
#include "Arduino.h"
#include "DefinedConstants.h"

class RGBControl {
  private:
    int DCVal;
    int counter;
    int sumDCVal;
    int upFade;
    int downFade;
    bool DCValCalculated;
  public:
    int ledPin;
    int brightness;
    int lastBrightness;
    int micVal;
    int micMax;
    int micMin;

    RGBControl(const RGBControl &object);
    RGBControl(int pinNum, int upFadeNum, int downFadeNum);
    void setBrightnessZero();
    void setLedPin(int pinNum);
    void setDCVal(int newDCVal);
    void setFade(int newUpFade, int newDownFade);
    void setMinMax (int newMin, int newMax);
    void micVal2Brightness();
    void writeBright();
    int calcDC();
    void printDC();
};

#endif // __RGBCONTROL_HEADER__

