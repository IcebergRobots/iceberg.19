#ifndef global_h
#define global_h

#include "Utility.h"
#include "Camera.h"
#include "Light.h"
#include "Display.h"

// Variablen müssen auch in core.h als extern implementiert werden.
bool silent = false;
bool hasDebugHead = true;

unsigned long lastSegment = 0;
unsigned long lastLoop = 0;

#endif