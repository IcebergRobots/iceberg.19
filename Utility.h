#ifndef Utility_h
#define Utility_h

#include "IO.h"
#include "Ultrasonic.h"
#include "Pilot.h"
#include "Line.h"
#include <avr/wdt.h>
#include "Reflexion.h"

#define SEGMENT_OFF    0
#define SEGMENT_EMPTY  1
#define SEGMENT_FILLED 2

void handleKeyEvents();
void kick();

void initUART();
void initI2C();
void setupWatchdog();
void loopWatchdog();
void setupDone();

void startSound();


void initEEPROM();
void initStates();
void updateStates();

void updateKick();

void initPui();

#endif
