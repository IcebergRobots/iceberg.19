#ifndef core_h
#define core_h

#include "Arduino.h"
#include "LinkedList.h"
#include "Pixy.h"
// #include <I2C.h>
#include <EEPROM.h>

// MODULES
#define DISPLAY_ENABLED     0
#define PUI_ENABLED         1
#define ORIENTATION_ENABLED 1
#define CAMERA_ENABLED      1
#define REFLEXION_ENABLED   1
#define LIGHT_ENABLED       1
#define LINE_ENABLED        1
#define KICKER_ENABLED      1

// Fahren
#define ROLE_COOLDOWN 1000      // [0 bis *]~1000 Zeitspanne, in dem kein Rollenwechsel stattfindet
#define ANGLE_SIDEWAY 90       // [0 bis 180]~100
#define ANGLE_GOAL 80           // [0 bis 180]~80 Winkel für Tordrehung
#define ANGLE_GOAL_MAX 45       // [0 bis 180]~45 maximaler Orientierungswinkel zum Tor
#define ANGLE_PASSIVE_MAX 35    // [0 bis 180]~45 maximaler Orientierungswinkel beim Zurückfahren
#define ANGLE_TURN_MAX 90       // [0 bis 180]~90 maximaler Orientierungswinkel zur Ballsuche
#define ANGLE_RETURN_MIN 20     // [0 bis 180]~90 minimaler Orientierungswinkel beim Zurücckdrehen
#define ANGLE_CENTER 15         // [0 bis 180]~15 Toleranz für mittige Objekte
#define ROTATION_SIDEWAY 100    // [0 bis *]~100
#define ROTATION_AWAY 40        // [0 bis *]~40
#define ROTATION_18CM 50        // [0 bis *]~70
#define ROTATION_10CM 70        // [0 bis *]~90
#define ROTATION_TOUCH 40       // [0 bis *]~20
#define SPEED_BACKWARDS 60      // [0 bis 255]~70  STATUS 0: Nach hinten
#define SPEED_PENALTY 40        // [0 bis 255]~50  STATUS 0: Nach hinten
#define SPEED_KEEPER 60        // [0 bis 255]~60  STATUS 1: Torverteidigung
#define SPEED_FREE 70           // [0 bis 255]~70 STATUS 4: Befreiung
#define SPEED_LOST 60          // [0 bis 255]~100 STATUS 5: Seitlich verloren
#define SPEED_SIDEWAY 60       // [0 bis 255]~100  STATUS 6: Ballverfolgung
#define SPEED_BALL 45          // [0 bis 255]~72  STATUS 6: Ballverfolgung
#define SPEED_BALL_FAR 50      // [0 bis 255]~72  STATUS 6: Ballverfolgung
#define SPEED_CLOSE 45         // [0 bis 255]~60 STATUS 7: Torausrichtung
#define SPEED_ATTACK 60        // [0 bis 255]~100 STATUS 8: Angriff
#define SPEED_AVOID_MATE 100   // [0 bis 255]~100 STATUS 9: Ausweichen
#define SPEED_DRIFT 80         // [0 bis 255]~140
#define SPEED_LINE 70           // [0 bis 255]~90
// TIMES
#define BACKWARD_MAX_DURATION 4000    // wann darf frühestens eingegriffen werden
#define GOAL_STUCK_DURATION 500       // wie lange soll nach vorne gefahren werden?
#define SIDEWARD_MAX_DURATION 2000    // max Zeit für Seitwärtsfahren
#define SIDEWARD_MIN_DURATION 1000     // min Zeit für Seitwärtsfahren
#define TURN_MAX_DURATION 1500        // max Zeit für Drehmodus
#define RETURN_MAX_DURATION 1500      // max Zeit für Drehmodus zurück
#define LOST_DURATION 700      // max Zeit für Ausweichmanöver
#define ROLE_LED_DURATION 350         // wie lange soll die Spielrolle angezeigt werden?
#define LINE_DURATION 300             // wie lange steuern wir der Linie entgegen?
#define HEADSTART_DURATION 350        // wie lange fahren wir volle Geschwindigkeit?
#define AVOID_MATE_DURATION 200       // wie lange weichen wir aus
#define DRIFT_DURATION 200            // wie lange steuern wir einem Drift entgegen?
#define PIXY_RESPONSE_DURATION 20000  // wie lange soll die Pixy-Led grün nachleuchten?

// BATTERY
#define BATTERY_MIN_VOLTAGE 110

// UART
#define DEBUG_SERIAL        Serial
#define DEBUG_BAUDRATE      115200
#define BLUETOOTH_ENABLED   1
#define BLUETOOTH_SERIAL    Serial1
#define BLUETOOTH_BAUDRATE  115200
#define BLACKBOX_ENABLED    1
#define BLACKBOX_SERIAL     Serial2
#define BLACKBOX_BAUDRATE   115200
#define BOTTOM_SERIAL       Serial3
#define BOTTOM_BAUDRATE     115200
#define START_MARKER        254     // Startzeichen einer Bluetooth-Nachricht
#define END_MARKER          255     // Endzeichen einer Bluetooth-Nachricht

// Feld
#define COURT_REARWARD_MAX 35           // optimaler Abstand nach hinten
#define COURT_REARWARD_MIN 25           // optimaler Abstand nach hinten
#define COURT_WIDTH 150         // Summe der Abstände nach rechts und links
#define COURT_BORDER_MIN 50     // Abstand nach rechts bzw. links am Torpfosten
#define COURT_WIDTH_FREE 140
#define COURT_POST_TO_BORDER 110 // Abstand nach rechts bzw. links am Torpfosten
#define MAX_DISTANCE 200

// PID-Regler Kompassausrichtung
#define HEADING_PID_P .27  // [0 bis *]~.27 p:proportional
#define HEADING_PID_I .02  // [0 bis *]~0   i:vorausschauend
#define HEADING_PID_D .03  // [0 bis *]~.03 d:Schwung herausnehmen (nicht zu weit drehen)

// PID-Regler Ball
#define TRACKING_PID_P .7  // [0 bis *]~.27 p:proportional
#define TRACKING_PID_I .0  // [0 bis *]~0   i:vorausschauend
#define TRACKING_PID_D .0  // [0 bis *]~.03 d:Schwung herausnehmen

//EEPROM Adressen
#define REFLEXION_THRESHOLD 2


// WATCHDOG
#define WDTO_OFF -1
/*gemessen  theoretisch
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
    -1mS    WDTO_OFF */
#define WATCHDOG_SETUP  WDTO_OFF // Setupzeit, nach der Neugestartet wird
#define WATCHDOG_LOOP   WDTO_OFF  // Schleifenzeit, nach der Neugestartet wird

// PIYX
#define SIGNATURE_BALL 1                      // Pixy-Signature des Balls
#define SIGNATURE_GOAL 2                      // Pixy-Signature des Tors
#define X_CENTER ((PIXY_MAX_X-PIXY_MIN_X)/2)  // PIXY: Die Mitte des Bildes der Pixy (in Pixeln)
#define BALL_WIDTH_TRIGGER 40                 // Schwellwert eines großen Balles
#define BALL_CENTER_TOLERANCE 40              // Toleranzwinkel für mittlere Bälle

//ULTRASONIC
#define I2C_US_FRONT_LEFT 112
#define I2C_US_LEFT 113
#define I2C_US_BACK 114
#define I2C_US_RIGHT 115
#define I2C_US_FRONT_RIGHT 116

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

bool isFinite(unsigned long value);
bool isFinite(unsigned int value);
bool isFinite(byte value);

int circulate(int value, int min, int max);
int pinMode(byte pin);
//void reset();
bool blink(unsigned long period, float proportion);
long mapConstrain(long x, long in_min, long in_max, long out_min, long out_max);

void beginSegment(String name="");
void endSegment();
extern void (*beginSegmentFunction)(String);
extern void (*endSegmentFunction)();

#endif
