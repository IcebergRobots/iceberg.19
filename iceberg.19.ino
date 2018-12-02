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

  if (key.decreasePage().click())         {} // display.changePage(1);
  if (key.increasePage().click())         {} // display.changePage(-1);
  if (key.selectPage().stroke())          {} // display.setMenu(0);
  if (key.selectPage().permanent())       {} // display.setPage(0);
  if (key.resetProperties().stroke())     {} // resetProperties();
  if (key.selectMenu().stroke())          {} // display.toggle();
  if (key.selectMenu().permanent())       {} // display.resetValue();
  if (key.kick().click())                 {} // kick();
  if (key.compassCalibration().click())   {} // activate calibration
  if (key.animation().stroke())           {} // activate animation
  if (key.animation().permanent())        {} // hymne
  if (key.lineCalibration().stroke())     {} // activate line calibration, setpage, setmenu to value
  if (key.lightBeamCalibration().click()) {} // activate light beam calibration, setpage, setmenu to value
  if (key.start().stroke())               {} // start motors, activate bluetooth
  if (key.stop().stroke())                {} // stop motors, activate bluetooth
  if (key.record().stroke())              {} // start / stop recording, activate bluetooth
  if (key.headstart().stroke())           {} // ?
  if (key.motor().stroke())               {} // ?
  if (key.bluetooth().stroke())           {} // activate bluetooth
  if (key.kicker().stroke())              {} // ?
  if (key.bottom().stroke())              {} // activate light
  if (key.debug().stroke())               {} // send hello

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

