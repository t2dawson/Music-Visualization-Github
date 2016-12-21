#ifndef __SERIAL_LOGGER__HEADER__
#define __SERIAL_LOGGER__HEADER__

#include "Arduino.h"
#include "DefinedConstants.h"

class SerialLogger {

    bool enabled;
    static SerialLogger* instance;
    SerialLogger();

  public:
    static SerialLogger* getInstance();
    void logDataToConsole(char* dataString);
    void enableLogger();
    void disableLogger();
};

#endif // __SERIAL_LOGGER__HEADER
