#ifndef global_h
#define global_h

#include "Utility.h"
#include "PixyCam.h"
#include "Light.h"
#include "Display.h"

// Variablen müssen auch in core.h als extern implementiert werden.
bool silent = false;
bool hasDebugHead = true;

int ball = 0;           // Abweichung der Ball X-Koordinate
int ballWidth = 0;      // Ballbreite
int ballArea = 0;       // Ballgröße (Flächeninhalt)
int goal = 0;           // Abweichung der Tor X-Koordinate
int goalWidth = 0;      // Torbreite
int goalArea = 0;       // Torgröße (Flächeninhalt)

unsigned long lastSegment = 0;
unsigned long lastLoop = 0;
unsigned long seeBallTimer = 0;   // Zeitpunkt des letzten Ball Sehens
unsigned long seeGoalTimer = 0;   // Zeitpunkt des letzen Tor Sehens
unsigned long closeBallTimer = 0; // Zeitpunkt des letzten großen Balls
unsigned long driftTimer = 0;     // Zeitpunkt seit wann wir gegensteuern
unsigned long ballLeftTimer = 0;  // Zeitpunkt wann der Ball zuletzt links war
unsigned long ballRightTimer = 0; // Zeitpunkt wann der Ball zuletzt rechts war
unsigned long pixyResponseTimer = 0;  // Zeitpunkt der letzten Antwort der Pixy
unsigned long pixyTimer = 0;  // Zeitpunkt des letzten Auslesens der Pixy

#endif