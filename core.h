#ifndef core_h
#define core_h

#include "Arduino.h"
#include "LinkedList.h"

// MODULES
#define DISPLAY_ENABLED     0
#define PUI_ENABLED         0
#define ORIENTATION_ENABLED 0
#define CAMERA_ENABLED      0
#define LIGHT_ENABLED       0

// UART
#define DEBUG_SERIAL        Serial
#define DEBUG_BAUDRATE      115200
#define BLUETOOTH_ENABLED   1
#define BLUETOOTH_SERIAL    Serial1
#define BLUETOOTH_BAUDRATE  115200
#define BLACKBOX_ENABLED    1
#define BLACKBOX_SERIAL     Serial2
#define BLACKBOX_BAUDRATE   115200

// DEBUG
#define DEBUG_ENABLED       1
#define DEBUG_SEGMENT       1       // sollen Methoden gezeigt werden?
#define DEBUG_LOOP          1       // soll jeder Schleifendurchlauf gezeigt werden?
#define DEBUG_BLUETOOTH     1       // sollen bluetooth nachrichten gezeigt werden?
#define DEBUG_SERIAL        Serial  // Serial der Usb-Schnittstelle
#define START_MARKER        254     // Startzeichen einer Bluetooth-Nachricht
#define END_MARKER          255     // Endzeichen einer Bluetooth-Nachricht

// 
#define BALL_CENTER_TOLERANCE 40 

#define WDTO_OFF -1
/* WATCHDOG
  gemessen  theoretisch
  17mS      WDTO_15MS
  34mS      WDTO_30MS
  68mS      WDTO_60MS
  136mS     WDTO_120MS
  272mS     WDTO_250MS
  544mS     WDTO_500MS
  1088mS    WDTO_1S
  2176mS    WDTO_2S
  4352mS    WDTO_4S
  8705mS    WDTO_8S
  -1  mS    WDTO_OFF
*/

#define WATCHDOG_SETUP  WDTO_OFF // Setupzeit, nach der Neugestartet wird
#define WATCHDOG_LOOP   WDTO_2S  // Schleifenzeit, nach der Neugestartet wird

// PIYX
#define SIGNATURE_BALL 1                      // Pixy-Signature des Balls
#define SIGNATURE_GOAL 2                      // Pixy-Signature des Tors
#define X_CENTER ((PIXY_MAX_X-PIXY_MIN_X)/2)  // PIXY: Die Mitte des Bildes der Pixy (in Pixeln)
#define BALL_WIDTH_TRIGGER 40                 // Schwellwert eines großen Balles
#define BALL_ANGLE_TRIGGER 40                 // Schwellenwert der Ballrichtung

// DATA TYPES
#define INT8_T_MIN          -128
#define INT8_T_MAX           127
#define UINT8_T_MIN            0
#define UINT8_T_MAX          255
#define INT16_T_MIN       -32768
#define INT16_T_MAX        32767
#define UINT16_T_MIN           0
#define UINT16_T_MAX       65535
#define INT32_T_MIN  -2147483648
#define INT32_T_MAX   2147483647
#define UINT32_T_MIN           0
#define UINT32_T_MAX  4294967295

// Zeitumwandlung
#define MILS_PER_SEC  (1000UL)  // Millisekunden pro Sekunde
#define MILS_PER_MIN  (60000UL) // Millisekunden pro Minute
#define SECS_PER_MIN  (60UL)    // Sekunden pro Minute
#define MINS_PER_HOUR (60UL)   // Minuten pro Stunde

#define numberOfSeconds(_millis_) ((_millis_ / MILS_PER_SEC) % SECS_PER_MIN)  // TIME: wandle Zeit in Sekundenanzeige um
#define numberOfMinutes(_time_) (_time_ / MILS_PER_MIN) % MINS_PER_HOUR       // TIME: wandle Zeit in Minutenanzeige um

// DISPLAY
#define SETUP_MESSAGE_RANGE 5 // [0 bis *] Anzahl von Schritten im Setup

#ifndef ARDUINO_AVR_MEGA2560
#error "Wrong board selected! Choose Mega 2560"
#endif

void debugln(long num, bool space=true);
void debugln(String str="", bool space=true);
void debug(long num, bool space=true);
void debug(String str="", bool space=true);
extern void (*debugFunction)(String, bool);

bool isFinite(unsigned long value);
bool isFinite(unsigned int value);
bool isFinite(byte value);

int circulate(int value, int min, int max);
int pinMode(byte pin);
void reset();
String format(String str, unsigned int minLength=0, unsigned int maxLength=-1);
String format(long num, unsigned int minLength=0, unsigned int maxLength=-1, bool sign=false);

void beginSegment(String name="");
void endSegment();
extern void (*beginSegmentFunction)(String);
extern void (*endSegmentFunction)();

#endif
