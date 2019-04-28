#ifndef Utility_h
#define Utility_h

#include "Config.h"
#include "Input.hpp"

void reset();
int shift(int &value, int min, int max);
void startSound();
void calculateStates();
void transmitHeartbeat();
void setupMotor();
void avoidLine();
void kick();
void readCompass();
void buzzerTone(int duration);
int ausrichten(int orientation);
void readPixy();
void rating();
String boolToSign(bool b);

void debug(String str);
void debug(long num);
void debug();
void debugln(String str);
void debugln(long num);
void debugln();

void handleBluetooth();
void handleStartStop();
void handleMenu();
#endif
