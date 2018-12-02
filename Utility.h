#ifndef Utility_h
#define Utility_h

#include "Core.h"

void reset();
int shift(int &value, int min, int max);
void startSound();
void calculateStates();

void debug(String str);
void debug(long num);
void debug();
void debugln(String str);
void debugln(long num);
void debugln();

void prepareDebug();
int pinMode(uint8_t pin);

#endif
