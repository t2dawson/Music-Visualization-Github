#ifndef __SERIAL_LOGGER__HEADER__
#define __SERIAL_LOGGER__HEADER__
#define BAUD_RATE 57600

class SerialLogger {

    bool enabled;
    static SerialLogger* instance;
    SerialLogger();

  public:
    static SerialLogger* getInstance();
    void logDataToConsole(char* dataString);
    void enableLogger();
    void disableLogger();
    ~SerialLogger();
};

#endif // __SERIAL_LOGGER__HEADER
