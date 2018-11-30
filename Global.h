#ifndef Global_h
#define Global_h

#include "Camera.h"
#include "Light.h"
#include "Key.h"
#include "Display.h"

bool silent = false;
bool hasDebugHead = false;

Camera camera; 
Display d = Display(D_PIN_3); // OBJEKTINITIALISIERUNG
Key key;
Light light;

#endif