#include "include.h"

void setup() {
  setupWatchdog();
  initUART();
  initDebug();
  initI2C();
  initStates();

  light.init();
  initPui();
  d.init();  // initialisiere Display mit Iceberg Schriftzug
  camera.init();
  orientation.init();
  //createCrashlog();
  //restoreSession();
  setupDone();

  /*****************************************************/
  io.turbo.setLimits(false, false); // set broken turbo key to off
  io.batteryVoltmeter.startDebug();
  /*for(int i = 0; i < 4; i++) {
    drive.m[i].speed->showDebug(DEBUG_PIN);
    drive.m[i].speed->startDebug();
  }*/

  //drive.brake();
  //drive.execute();
  /*****************************************************/
}

void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  
  loopWatchdog();
  io.update();

  digitalWrite(io.buzzer.getPin(), false);
  digitalWrite(io.speaker.getPin(), false);

  if (orientation.onDemand()) orientation.update();
  if (camera.onDemand()) camera.frame();
  //readUltrasonic();

  if (io.decreasePage.click())         {  /*d.changePage(-1);  */                                           }
  if (io.increasePage.click())         {  /*d.changePage(1);   */                                           }
  if (io.selectPage.click())           {  /*d.toggle();        */                                           }
  if (io.decreaseMenu.click())         {  /*d.scroll(-1);      */                                           }
  if (io.increaseMenu.click())         {  /*d.scroll(1);       */                                           }
  if (io.selectMenu.click())           {  debug("selectMenu");                                              }
  if (io.testKick.click())             {  debug("testKick");                                                }
  if (io.compassCalibration.click())   {  debug("compassCalibration");                                      }
  if (io.animation.click())            {  debug("animation");                                               }
  if (io.lineCalibration.click())      {  io.headingOffset.set(io.heading.get() + io.headingOffset.get());  }
  if (io.ballTouchCalibration.click()) {  debug("ballTouchCalibration");                                    }
  if (io.start.click())                {  io.pause.set(false);                                        }
  if (io.stop.click())                 {  io.pause.set(true);                                       }
  
  if (io.record.click())               {  debug("record");                                                  }      
  if (io.resetProperties.click())      {  debug("resetProperties");                                         }              
  if (io.kickerStart.click())          {  debug("kickerStart");     io.kickPermanent.set(true);             }          
  if (io.kickerStop.click())           {  debug("kickerStop");      io.kickPermanent.set(false);            }          
  if (io.shiftStart.click())           {  debug("shiftStart");                                              }          
  if (io.shiftStop.click())            {  debug("shiftStop");                                               }        
/*
  if (io.drivePower.outsidePeriod(400)) drive.brake(false);
  if (io.driveEnabled.falling()) drive.brake(false);
  if (io.driveEnabled.off() && io.driveEnabled.outsidePeriod(100)) drive.brake(false);
*/

  updateStates();
//updateRating();
  //updateKick();
  //updateAnimation();

  //calibrateGoal();
  //calibrateLightBeam();
  //calibrateLine();
  //drive.prepare();
  drive.update();
  drive.execute();
  if (light.onDemand()) light.light();
  //bluetoth();
  if (d.onDemand()) d.update();
}

