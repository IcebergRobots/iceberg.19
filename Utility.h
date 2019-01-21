#ifndef Utility_h
#define Utility_h

#include "core.h"

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

#endif
