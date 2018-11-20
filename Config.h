#ifndef Config_h
#define Config_h

#include "Arduino.h"
#include "Camera.h"
#include "Utility.h"
#include "pin.h"

#include <SPI.h>
#include <Wire.h>

void setupPinmodes();
void setupSPI();
void setupUART();
void setupI2C();

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
#define DEBUG_STATE true          // soll der Statuswechsel gezeigt werden?
#define DEBUG_FUNCTIONS false     // sollen Methoden gezeigt werden?
#define DEBUG_LOOP false          // soll jeder Schleifendurchlauf gezeigt werden?
#define DEBUG_BLUETOOTH true      // sollen bluetooth nachrichten gezeigt werden?
#define DEBUG_SERIAL Serial       // Serial der Usb-Schnittstelle
#define START_MARKER 254          // Startzeichen einer Bluetooth-Nachricht
#define END_MARKER 255            // Endzeichen einer Bluetooth-Nachricht

extern bool silent, hasDebugHead;

#endif
