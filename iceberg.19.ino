#include "core.h"    // Lade fundamentale Daten, die alle benötigen: Einstellungen, Pintabelle, Basiswerkzeuge, Bibliotheken
#include "basic.h" // Lade Ein- und Ausgabe
IO io;               // Ermögliche Ein- und Ausgabe
#include "global.h"  // Lade alle aufwendigeren Klassen und Werkzeuze, Initialisiere globale Variablen / Objekte

void setup() {
  initUART();
  initDebug();
  initI2C();

  //d.init();  // initialisiere Display mit Iceberg Schriftzug
  //initCamera();

  //createCrashlog();
  //restoreSession();
  debugln("SETUP DONE");
  delay(1000);
}
void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  initWatchdog();

  //readCompass();
  //readPixy();
  //readUltrasonic();
  /*
  io.update();

  
  if (io.decreasePage.click())         {} // display.changePage(1);
  if (io.increasePage.click())         {} // display.changePage(-1);
  if (io.selectPage.stroke())          {} // display.setMenu(0);
  if (io.selectPage.permanent())       {} // display.setPage(0);
  if (io.resetProperties.stroke())     {} // resetProperties();
  if (io.selectMenu.stroke())          { debug("stroke"); } // display.toggle();
  if (io.selectMenu.permanent())       { debug("permanent"); } // display.resetValue();
  if (io.kick.click())                 {} // kick();
  if (io.compassCalibration.click())   {} // activate calibration
  if (io.animation.stroke())           {} // activate animation
  if (io.animation.permanent())        {} // hymne
  if (io.lineCalibration.stroke())     {} // activate line calibration, setpage, setmenu to value
  if (io.lightBeamCalibration.click()) {} // activate light beam calibration, setpage, setmenu to value
  if (io.start.stroke())               { debug("start"); } // start motors, activate bluetooth
  if (io.stop.stroke())                { debug("stop");  } // stop motors, activate bluetooth
  if (io.record.stroke())              {} // start / stop recording, activate bluetooth
  if (io.headstart.stroke())           {} // ?
  if (io.motor.stroke())               {} // ?
  if (io.bluetooth.stroke())           {} // activate bluetooth
  if (io.kicker.stroke())              {} // ?
  if (io.bottom.stroke())              {} // activate light
  if (io.debug.stroke())               {} // send hello
  */

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

