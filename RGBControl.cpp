#include "RGBControl.h"

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
  DCVal = 0;
  DCValCalculated == false;
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

void RGBControl::micVal2Brightness() {
  micVal = abs(micVal - DCVal);
  micMin = min(micVal, micMin);
  micMax = max(micVal, micMax);
  brightness = (int)(((float)(micVal - micMin) / (float)(micMax - micMin)) * MAXVALREL - 1);
  brightness = min(max(brightness - 20, 0), MAXVALREL - 1);
}

void RGBControl::writeBright() {
  counter = 0;
  while ( abs(lastBrightness - brightness) > FADEGAP / 2)
  {
    counter++;
    if (lastBrightness > brightness) {
      lastBrightness-- ;
      if (counter >= downFade) break;
    }
    else
    {
      lastBrightness++ ;
      if (counter >= upFade) break;
    }
    analogWrite(ledPin, lastBrightness);
  }
}

int RGBControl::calcDC() {
  if (!DCValCalculated)
  {
    if (counter >= WAKEUPSAMP) sumDCVal = sumDCVal + micVal;
    counter++;
    if (counter == (AVGNUM + WAKEUPSAMP))
    {
      DCVal = sumDCVal / AVGNUM;
      printDC();
      DCValCalculated == true;
      return 1;
    }
    return 0;
  }
  else
  {
    return 1;
  }
}

void RGBControl::printDC() {
  char printBuffer[4];
  sprintf(printBuffer, "DCVal= %i", DCVal);
  SerialLogger::getInstance()->logDataToConsole(printBuffer);
}

