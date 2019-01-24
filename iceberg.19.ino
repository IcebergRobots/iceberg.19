#include "include.h"   // Lade fundamentale Daten, die alle benötigen: Einstellungen, Pintabelle, Basiswerkzeuge, Bibliotheken
 // Lade alle aufwendigeren Klassen und Werkzeuze, Initialisiere globale Variablen

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
  for(int i = 0; i < 4; i++) {
    drive.m[i].speed->showDebug(DEBUG_PIN);
    drive.m[i].speed->startDebug();
  }
  /*****************************************************/
}

void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  loopWatchdog();
  io.update();

  //readCompass();
  if (camera.onDemand()) camera.frame();
  //readUltrasonic();
  
  
  if (io.shiftStart.further())               {
    debug("ball:");
    debug(io.ball.str(4, -1, true) + ",");
    debug(io.ballWidth.str(4) + ",");
    debug(io.ballArea.str(4));
  }
  if (io.shiftStop.further())                { 
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
    drive.brake(false);
  }

  if (io.drivePower.outsidePeriod(400)) drive.brake(false);
  if (io.driveEnabled.falling()) drive.brake(false);
  if (io.driveEnabled.off() && io.driveEnabled.outsidePeriod(100)) drive.brake(false);

  updateStates();
  //updateRating();
  //updateKick();
  //updateAnimation();

  //calibrateGoal();
  //calibrateLightBeam();
  //calibrateLine();

  if (light.onDemand()) light.light();
  drive.execute();
  //bluetoth();
  if (d.onDemand()) d.update();

  //camera.frame();
}

