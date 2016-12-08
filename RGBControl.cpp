#include "RGBControl.h"
#include "Arduino.h"

RGBControl::RGBControl (const RGBControl &object) {
  ledPin = object.ledPin;
  brightness = object.brightness;
  lastBrightness = object.lastBrightness;
  micVal = object.micVal;
  DCVal = object.DCVal;
  micMax = object.micMax;
  micMin = object.micMin;
  counter = object.counter;
  sumDCVal = object.sumDCVal;
  upFade = object.upFade;
  downFade = object.downFade;
}

RGBControl::RGBControl(int pinNum, int upFadeNum, int downFadeNum) {
  ledPin = pinNum;
  micVal = 0;
  DCVal = -1;
  brightness = 0;
  lastBrightness = 0;
  micMax = 0;
  micMin = 255; //1023;
  counter = 0;
  sumDCVal = 0;
  upFade = upFadeNum;
  downFade = downFadeNum;
}

void RGBControl::setBrightnessZero() {
  brightness = 0;
}

void RGBControl::setLedPin(int newLedPin) {
  ledPin = newLedPin;
}

void RGBControl::setFade(int newUpFade, int newDownFade) {
  upFade = newUpFade;
  downFade = newDownFade;
}

void RGBControl::setMinMax(int newMin, int newMax) {
  micMin = newMin;
  micMax = newMax;
}

void RGBControl::setDCVal(int newDCVal) {
  DCVal = newDCVal;
}

void RGBControl::micVal2Brightness(){
  micVal = abs(micVal - DCVal);
  micMin = min(micVal, micMin);
  micMax = max(micVal, micMax);
  brightness = (int)(((double)(micVal - micMin) / (double)(micMax - micMin)) * MAXVALREL) - 1;
  brightness = min(max(brightness - 10, 0), MAXVALREL - 1);
}

void RGBControl::writeBright() {
  counter = 0;
  while ( abs(lastBrightness - brightness) > FADEGAP / 2)
  {
    counter++;
    if (lastBrightness > brightness) {
      lastBrightness = lastBrightness - FADEGAP;
      if (counter >= downFade) break;
    }
    else
    {
      lastBrightness = lastBrightness + FADEGAP;
      if (counter >= upFade) break;
    }
    analogWrite(ledPin, lastBrightness);
  }
}

int RGBControl::calcDC() {
  if (DCVal == -1)
  {
    if (counter >= WAKEUPSAMP) sumDCVal = sumDCVal + micVal;
    counter++;
    if (counter == AVGNUM + WAKEUPSAMP )
    {
      DCVal = sumDCVal / AVGNUM;
      if (SENDSERIAL) {
        Serial.println(DCVal);
      }
      return 1;
    }
    return 0;
  }
  else
  {
    return 1;
  }
}
