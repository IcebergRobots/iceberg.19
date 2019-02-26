#include "include.h"

void setup() {
  setupWatchdog();
  initUART();
  initDebug();
  initI2C();
  initStates();

  light.init();
  pui.init(io.battery.on());
  d.init();  // initialisiere Display mit Iceberg Schriftzug
  camera.init();
  orientation.init();
  //createCrashlog();
  //restoreSession();
  setupDone();

  /*****************************************************/
  io.turbo.setLimits(false, false); // set broken turbo key to off
  for(int i = 0; i < 4; i++) {
    drive.m[i].speed->showDebug(DEBUG_PIN);
    drive.m[i].speed->startDebug();
  }
  io.seeBall.startDebug();
  io.ball.startDebug();
  io.state.startDebug();
  /*
  io.xOrientation.startDebug();
  io.yOrientation.startDebug();
  io.zOrientation.startDebug();
  */

  //drive.brake();
  //drive.execute();
  /*****************************************************/
}

void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  
  loopWatchdog();
  io.update();

  if (orientation.onDemand()) orientation.update();
  if (camera.onDemand()) camera.frame();
  //readUltrasonic();

  if (io.shiftStart.further()) {
    debug("ball:");
    debug(io.ball.str(4, -1, true) + ",");
    debug(io.ballWidth.str(4) + ",");
    debug(io.ballArea.str(4));
  }
  if (io.shiftStop.further()) { 
    debug("goal:");
    debug(io.goal.str(4, -1, true) + ",");
    debug(io.goalWidth.str(4) + ",");
    debug(io.goalArea.str(4));
  }

  if (io.start.stroke()) {
    debug("start");
    io.driveEnabled.set(true);
  }
  if (io.stop.stroke()) {
    debug("stop");
    io.driveEnabled.set(false);
  }
  if (io.shiftStart.click()) {
    drive.steer();
    drive.accelerate(io.poti.get());
    drive.face();
  }
  if (io.shiftStop.click()) {
    debug(io.xOrientation.str());
    debug(io.yOrientation.str());
    debug(io.zOrientation.str());
  }
/*
  if (io.drivePower.outsidePeriod(400)) drive.brake(false);
  if (io.driveEnabled.falling()) drive.brake(false);
  if (io.driveEnabled.off() && io.driveEnabled.outsidePeriod(100)) drive.brake(false);
*/

  updateStates();
  refreshMotor();
//updateRating();
  //updateKick();
  //updateAnimation();

  //calibrateGoal();
  //calibrateLightBeam();
  //calibrateLine();
  drive.update();

  drive.execute();
  if (light.onDemand()) light.light();
  //bluetoth();
  if (d.onDemand()) d.update();
}

