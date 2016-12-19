#ifndef __LOGGING_FUNCTIONS__HEADER__
#define __LOGGING_FUNCTION__HEADER__
#include "RGBControl.h"

void printMicValues(int unfilteredVal, int RValue, int GValue, int BValue);
void printTimeData(long currentTime, long lastTime, int timeDiff);
void printBrightnessData(RGBControl &Robject, RGBControl &Gobject, RGBControl &Bobject);
void printMinMaxData(RGBControl &Robject, RGBControl &Gobject, RGBControl &Bobject);

#endif // __LOGGING_FUNCTIONS__HEADER__
