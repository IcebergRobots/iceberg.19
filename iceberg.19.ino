#include "start.h"

void setup() {
  initUART();
  initDebug();
  initI2C();
  pui.init();

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

  io.update();
  
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
  if (io.lineCalibration.stroke())     { debug("6"); } // activate line calibration, setpage, setmenu to value
  if (io.lightBeamCalibration.click()) { debug("7"); } // activate light beam calibration, setpage, setmenu to value
  if (io.start.stroke())               {
    debug("start");
  } // start motors, activate bluetooth
  if (io.stop.stroke())                { debug("stop");  } // stop motors, activate bluetooth
  if (io.record.stroke())              { debug("0"); } // start / stop recording, activate bluetooth
  if (io.headstart.stroke())           { debug("1"); } // ?
  if (io.motor.stroke())               { debug("2"); } // ?
  if (io.bluetooth.stroke())           { debug("3"); } // activate bluetooth
  if (io.kicker.stroke())              { debug("4"); } // ?
  if (io.bottom.stroke())              { debug("5"); } // activate light
  if (io.debug.stroke())               { debug("6"); } // send hello

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

