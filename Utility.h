#ifndef Utility_h
#define Utility_h

#include "IO.h"
#include "Pilot.h"
#include <avr/wdt.h>

#define SEGMENT_OFF    0
#define SEGMENT_EMPTY  1
#define SEGMENT_FILLED 2

void kick();

void initUART();
void initI2C();
void initInterrupt();
void setupWatchdog();
void loopWatchdog();
void initDebug();
void setupDone();

void startSound();
void calculateStates();

void prepareDebug();

void initEEPROM();
void initStates();
void updateStates();

void printDebug(String str, bool space);
void printBeginSegment(String name);
void printEndSegment();

void initPui();

void updateLine();

#endif
