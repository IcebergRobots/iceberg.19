#ifndef Core_h
#define Core_h

#ifndef ARDUINO_AVR_MEGA2560
#error "Wrong board selected! Choose Mega 2560"
#endif

#include "Arduino.h"

#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <avr/wdt.h>
#include <I2C.h>
#include <SPI.h>

#include "Pintable.h"
#include "Key.h"
#include "Utility.h"



void initPins();
void initSPI();
void initUART();
void initI2C();

void initWatchdog();
void initDebug();

// UART
#define DEBUG true
#define DEBUG_SERIAL Serial
#define DEBUG_BAUDRATE 115200
#define BLUETOOTH true
#define BLUETOOTH_SERIAL Serial1
#define BLUETOOTH_BAUDRATE 115200
#define BLACKBOX false
#define BLACKBOX_SERIAL Serial2
#define BLACKBOX_BAUDRATE 115200

// DEBUG
#define DEBUG_STATE     true         // soll der Statuswechsel gezeigt werden?
#define DEBUG_FUNCTIONS false        // sollen Methoden gezeigt werden?
#define DEBUG_LOOP      false        // soll jeder Schleifendurchlauf gezeigt werden?
#define DEBUG_BLUETOOTH true         // sollen bluetooth nachrichten gezeigt werden?
#define DEBUG_SERIAL Serial       // Serial der Usb-Schnittstelle
#define START_MARKER 254          // Startzeichen einer Bluetooth-Nachricht
#define END_MARKER 255            // Endzeichen einer Bluetooth-Nachricht

// Zeitumwandlung
#define MILS_PER_SEC  (1000UL)  // Millisekunden pro Sekunde
#define MILS_PER_MIN  (60000UL) // Millisekunden pro Minute
#define SECS_PER_MIN  (60UL)    // Sekunden pro Minute
#define MINS_PER_HOUR (60UL)   // Minuten pro Stunde

#define numberOfSeconds(_millis_) ((_millis_ / MILS_PER_SEC) % SECS_PER_MIN)  // TIME: wandle Zeit in Sekundenanzeige um
#define numberOfMinutes(_time_) (_time_ / MILS_PER_MIN) % MINS_PER_HOUR       // TIME: wandle Zeit in Minutenanzeige um

// DISPLAY
#define SETUP_MESSAGE_RANGE 10 // [0 bis *] Anzahl von Schritten im Setup

// DATA TYPES
#define INT8_T_MIN -128
#define INT8_T_MAX 127
#define UINT8_T_MIN 0
#define UINT8_T_MAX 255
#define INT16_T_MIN -32768
#define INT16_T_MAX 32767
#define UINT16_T_MIN 0
#define UINT16_T_MAx 65535
#define INT32_T_MIN -2147483648
#define INT32_T_MAX 2147483647
#define UINT32_T_MIN 0
#define UINT32_T_MAX 4294967295
#define INT64_T_MIN −9223372036854775808
#define INT64_T_MAX 9223372036854775807
#define UINT64_T_MIN 0
#define UINT64_T_MAX 18446744073709551615

extern bool silent, hasDebugHead;


/*
data type         │  min      │   max
══════════════════╪═══════════╪═══════
bool, boolean      0            1 
char               -128         127
byte               0            255
short

unsigned short

int

unsigned int

long

uint64_t

long long

uint64_t long

float

double


*/

#endif
