#include "LoggingFunctions.h"
#include "SerialLogger.h"

void printMicValues(int unfilteredVal, int RValue, int GValue, int BValue) {
  char printBuffer[40];
  sprintf(printBuffer, "NoFiltVal: %d, MicVal: R= %d, G= %d, B= %d", unfilteredVal, RValue, GValue, BValue);
  SerialLogger::getInstance()->logDataToConsole(printBuffer);
}
void printTimeData(long currentTime, long lastTime, int timeDiff) {
  char printBuffer[40];
  sprintf(printBuffer, "CurrentTime= %ul, LastTime= %ul, TimeDiff= %d", currentTime, lastTime, timeDiff);
  SerialLogger::getInstance()->logDataToConsole(printBuffer);

}
void printBrightnessData(RGBControl &Robject, RGBControl &Gobject, RGBControl &Bobject) {
  char printBuffer[40];
  sprintf(printBuffer, "Bright: R= %d,G= %d,B= %d  LastBright: R= %d,G= %d,B= %d", Robject.brightness, Gobject.brightness, Bobject.brightness, Robject.lastBrightness, Gobject.lastBrightness, Bobject.lastBrightness);
  SerialLogger::getInstance()->logDataToConsole(printBuffer);
}
void printMinMaxData(RGBControl &Robject, RGBControl &Gobject, RGBControl &Bobject) {
  char printBuffer[40];
  sprintf(printBuffer, "MicMin: R= %d,G= %d,B= %d, MicMax: R= %d,G= %d, B= %d", Robject.micMin, Gobject.micMin, Bobject.micMin, Robject.micMax, Gobject.micMax, Bobject.micMax);
  SerialLogger::getInstance()->logDataToConsole(printBuffer);
}

