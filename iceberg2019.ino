#include "Config.h"

bool silent = false;
bool hasDebugHead = false;

Display d = Display(D_PIN_3); // OBJEKTINITIALISIERUNG
Camera camera;  // OBJEKTINITIALISIERUNG

void setup() {
  initPins();
  initUART();
  initI2C();

  d.init();  // initialisiere Display mit Iceberg Schriftzug
  //initCamera();

  //createCrashlog();
  //restoreSession();
  initDebug();
  delay(1000);
}
void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  initWatchdog();

  debug(",");
  byte num = constrain(map(abs(int(millis() % 500) - 250),0,250,-100,356),0,255);
  debug(num);
  analogWrite(IND_HEARBEAT, num);
  digitalWrite(PUI_LIGHT, (millis()%500)<250);
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

  //light();
  //pilot();
  //bluetoth();
  //display();

  //camera.frame();
}

