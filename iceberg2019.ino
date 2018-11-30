#include "Core.h"   // Lade fundamentale Daten, die alle benötigen: Einstellungen, Pintabelle, Basiswerkzeuge, Bibliotheken
#include "Global.h" // Lade alle aufwendigeren Klassen und Werkzeuze, Initialisiere globale Variablen / Objekte

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
  //readPui();
  key.update();

  if (key.start().permanent())  debug("start");
  if (key.stop().stroke())      debug("stop");
  if (key.selectMenu().click()) debug("select");

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
  delay(10);
}

