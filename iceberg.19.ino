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
  

  if(io.start.stroke()) {
    debug("start");
    drive.set(0, 255);
  }
  if(io.stop.stroke()) {
    debug("stop");
    drive.brake(1);
  }
  if (io.shiftStart.stroke())               {
    debug("ball:");
    debug(io.ball.str(4, -1, true) + ",");
    debug(io.ballWidth.str(4) + ",");
    debug(io.ballArea.str(4));
  }
  if (io.shiftStop.stroke())                { 
    debug("goal:");
    debug(io.goal.str(4, -1, true) + ",");
    debug(io.goalWidth.str(4) + ",");
    debug(io.goalArea.str(4));
  }

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

