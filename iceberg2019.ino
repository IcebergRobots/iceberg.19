#include "Config.h"

bool silent = false;
bool hasDebugHead = false;

// OBJEKTINITIALISIERUNG
Camera camera; 
Display d = Display(D_PIN_3); // OBJEKTINITIALISIERUNG
Key key;
Light light;

void setup() {
  initPins();
  initUART();
  initI2C();

  //d.init();  // initialisiere Display mit Iceberg Schriftzug
  //initCamera();

  //createCrashlog();
  //restoreSession();
  initDebug();
  delay(1000);
}
void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  initWatchdog();

  //readCompass();
  //readPixy();
  //readUltrasonic();
  //readPui(); page menu start stop lever

  //updateStates();
  //updateRating();
  //updateKick();
  //updateAnimation();

  //calibrateGoal();
  //calibrateLightBeam();
  //calibrateLine();

  light.light();
  //pilot();
  //bluetoth();
  //display();

  //camera.frame();
}

