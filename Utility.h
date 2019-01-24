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

void updateStates();

void printDown(String str, bool space);

#endif
