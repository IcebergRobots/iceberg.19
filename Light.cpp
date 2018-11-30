#include "Light.h"

/*****************************************************
  Konstruktor
*****************************************************/
Light::Light() {}

void Light::light() {
  analogWrite(IND_HEARBEAT, constrain(map(abs(int(millis() % 500) - 250),0,250,-100,356),0,255));
}