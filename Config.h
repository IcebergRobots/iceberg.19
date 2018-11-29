#ifndef Config_h
#define Config_h

#ifndef ARDUINO_AVR_MEGA2560
#error "Wrong board selected! Choose Mega 2560"
#endif

#include "Arduino.h"
#include <avr/wdt.h>
#include "Camera.h"
#include "Display.h"
#include "Input.h"
#include "Utility.h"
#include "pin.h"

#include <SPI.h>
#include <Wire.h>

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
#define DEBUG_LOOP      true         // soll jeder Schleifendurchlauf gezeigt werden?
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


extern bool silent, hasDebugHead;

#endif
