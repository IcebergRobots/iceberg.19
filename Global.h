#ifndef Global_h
#define Global_h

#include "Utility.h"
#include "Camera.h"
#include "Light.h"
#include "Display.h"

bool silent = false;
bool hasDebugHead = true;

Camera camera; 
//Display d = Display(D_PIN_3); // OBJEKTINITIALISIERUNG
Light light;
extern IO io;

#endif