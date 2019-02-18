#ifndef Utility_h
#define Utility_h

#include "IO.h"
#include <avr/wdt.h>

void initUART();
void initI2C();
void setupWatchdog();
void loopWatchdog();
void initDebug();
void setupDone();

void startSound();
void calculateStates();

void prepareDebug();

bool measureBatteryVoltage();
void updateStates();

void printDebug(String str, bool space);
void printBeginSegment(String name);
void printEndSegment();

#endif
