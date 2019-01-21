#include "core.h"   // Lade fundamentale Daten, die alle benötigen: Einstellungen, Pintabelle, Basiswerkzeuge, Bibliotheken
#include "global.h" // Lade alle aufwendigeren Klassen und Werkzeuze, Initialisiere globale Variablen

void setup() {
  setupWatchdog();
  initUART();
  initDebug();

  d.init();  // initialisiere Display mit Iceberg Schriftzug
  initI2C();
  pui.init();
  camera.init();
  //createCrashlog();
  //restoreSession();
  setupDone();

  /*****************************************************/
  io.turbo.setLimits(false, false); // set broken turbo key to off
  /*****************************************************/
}

void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  loopWatchdog();

  io.update();

  //readCompass();
  if (camera.onDemand()) camera.frame();
  //readUltrasonic();
  
  if (io.decreasePage.click())         {} // display.changePage(1);
  if (io.increasePage.click())         {} // display.changePage(-1);
  if (io.selectPage.stroke())          {} // display.setMenu(0);
  if (io.selectPage.permanent())       {} // display.setPage(0);
  if (io.resetProperties.stroke())     {} // resetProperties();
  if (io.selectMenu.stroke())          { debug("stroke"); } // display.toggle();
  if (io.selectMenu.permanent())       { debug("permanent"); } // display.resetValue();
  if (io.testKick.click())             {} // kick();
  if (io.compassCalibration.click())   {} // activate calibration
  if (io.animation.stroke())           {} // activate animation
  if (io.animation.permanent())        {} // hymne
  if (io.lineCalibration.stroke())     { /* debug("6"); */ } // activate line calibration, setpage, setmenu to value
  if (io.ballTouchCalibration.click()) { /* debug("7"); */ } // activate light beam calibration, setpage, setmenu to value
  if (io.start.stroke())               {
    debug("ball:");
    debug(io.ball.str(4, -1, true) + ",");
    debug(io.ballWidth.str(4), + ",");
    debug(io.ballArea.str(4));
  } // start motors, activate bluetooth
  if (io.stop.stroke())                { 
    debug("goal:");
    debug(io.goal.str(4, -1, true) + ",");
    debug(io.goalWidth.str(4) + ",");
    debug(io.goalArea.str(4));
  } // stop motors, activate bluetooth
  if (io.record.stroke())              { debug("record");  } // start / stop recording, activate bluetooth
  if (io.headstart.stroke())           { /* debug("1"); */ } // ?
  if (io.motor.stroke())               { /* debug("2"); */ } // ?
  if (io.bluetooth.stroke())           { /* debug("3"); */ } // activate bluetooth
  if (io.kicker.stroke())              { /* debug("4"); */ } // ?
  if (io.bottom.stroke())              { /* debug("5"); */ } // activate light
  if (io.turbo.stroke())               { /* debug("6"); */ } // send hello

  updateStates();
  //updateRating();
  //updateKick();
  //updateAnimation();

  //calibrateGoal();
  //calibrateLightBeam();
  //calibrateLine();

  if (light.onDemand()) light.light();
  //pilot();
  //bluetoth();
  if (d.onDemand()) d.update();

  //camera.frame();
}

