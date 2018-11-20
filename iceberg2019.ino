#include "Config.h"

bool silent = false;
bool hasDebugHead = false;

Camera camera;  // OBJEKTINITIALISIERUNG

void setup() {
  setupPinmodes();
  setupUART();
  setupI2C();
  camera.init();
}
void loop() {
  hasDebugHead = false;
  if (DEBUG_LOOP) debug();
  
  camera.frame();
  delay(1);
}

