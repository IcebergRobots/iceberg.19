#ifndef Global_h
#define Global_h

#include "Camera.h"
#include "Light.h"
#include "Pui.h"
#include "Display.h"

bool silent = false;
bool hasDebugHead = true;

Camera camera; 
Display d = Display(D_PIN_3); // OBJEKTINITIALISIERUNG
Light light;
Pui key;

#endif