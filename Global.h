#ifndef global_h
#define global_h

#include "Utility.h"
#include "Camera.h"
#include "Light.h"
#include "Display.h"

bool silent = false;
bool hasDebugHead = true;

Camera camera; 
Display d = Display(io.test1.getPin()); // OBJEKTINITIALISIERUNG
Light light;

#endif