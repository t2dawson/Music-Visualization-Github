#include "SerialLogger.h"


SerialLogger* SerialLogger::instance = NULL;

SerialLogger::SerialLogger() {
  Serial.begin(BAUD_RATE);
  enabled = true;
}

void SerialLogger::enableLogger() {
  enabled = true;
}

void SerialLogger::disableLogger() {
  enabled = false;
}

SerialLogger* SerialLogger::getInstance() {
  if (!instance) {
    instance = new SerialLogger();
  }
  return instance;
}

void SerialLogger::logDataToConsole(char* dataString) {
  if (!enabled) {
    return;
  }
  Serial.print(dataString);
}




