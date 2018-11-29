#ifndef Utility_h
#define Utility_h

#include "Config.h"

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

#endif
