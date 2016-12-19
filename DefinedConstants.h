#ifndef __DEFINED_CONSTANTS__HEADER__
#define __DEFINED_CONSTANTS__HEADER__

// Constants for defining the size of analog value buffers and filtertaps for fir filter
#define BUFFER 20
#define FILTERTAPS 30

//constants for default RBG gain values
#define DEFAULT_R_GAIN 1
#define DEFAULT_G_GAIN 0.5
#define DEFAULT_B_GAIN 2

//constants for default RGB fade values
#define DEFAULT_R_UPFADE 50
#define DEFAULT_R_DOWNFADE 20
#define DEFAULT_G_UPFADE 50
#define DEFAULT_G_DOWNFADE 7
#define DEFAULT_B_UPFADE 50
#define DEFAULT_B_DOWNFADE 2

//constants for default starting RGB min,max values
#define INITIAL_RGB_MAX 0
#define INITIAL_RGB_MIN 255

// constants for RGB and DC value processing
#define MAXVALREL 256
#define AVGNUM 30
#define WAKEUPSAMP 2
#define FADEGAP 2

// Default LED pin constants
#define LED_R 3
#define LED_G 5
#define LED_B 7

//constants for Serial Logging class
#define BAUD_RATE 57600
#define SENDSERIAL 1

#endif // __DEFINED_CONSTANTS__HEADER__ 

