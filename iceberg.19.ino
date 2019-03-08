#include "include.h"

void setup() {
  io.battery.setLimits(true, true);
  setupWatchdog();
  initUART();
  initDebug();
  initI2C();
  initEEPROM();
  initStates();
  io.battery.setLimits(true, true);

  light.init();
  initPui();
  d.init();  // initialisiere Display mit Iceberg Schriftzug
  camera.init();
  orientation.init();
  us.init();
  //createCrashlog();
  //restoreSession();
  setupDone();

  /*****************************************************/
  io.state.startDebug();
  io.drivePower.startDebug();
  digitalWrite(io.kick.getPin(), LOW);
  /*****************************************************/
}

void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  
  loopWatchdog();

  if (DEBUG_INFO) {
  }

  io.update();

  digitalWrite(io.buzzer.getPin(), false);
  digitalWrite(io.speaker.getPin(), false);

  if (orientation.onDemand()) orientation.update();
  if (camera.onDemand()) camera.frame();
  if (us.onDemand()) us.update();

  if (io.decreasePage.click())         {  /*d.changePage(-1);  */                                           }
  if (io.increasePage.click())         {  /*d.changePage(1);   */                                           }
  if (io.selectPage.click())           {  /*d.toggle();        */                                           }
  if (io.decreaseMenu.click())         {  /*d.scroll(-1);      */                                           }
  if (io.increaseMenu.click())         {  /*d.scroll(1);       */                                           }
  if (io.selectMenu.click())           {  debug("selectMenu");                                              }
  if (io.testKick.click())             {  kick();                                                           }
  if (io.compassCalibration.click())   {
    io.headingOffset.set(io.zOrientation.get());
    EEPROM.write(0, io.headingOffset.left());  // speichere Vorzeichen
    EEPROM.write(1, abs(io.headingOffset.get())); // speichere Winkel
  }
  if (io.animation.click())            {  debug("animation");                                               }
  if (io.lineCalibration.click())      {  BOTTOM_SERIAL.write(42);                                          }
  if (io.ballTouchCalibration.click()) {  debug("ballTouchCalibration");                                    }
  if (io.start.click())                {  io.pause.set(false);                                              }
  if (io.stop.click())                 {  io.pause.set(true);                                               }
  
  if (io.record.click())               {  debug("record");                                                  }      
  if (io.resetProperties.click())      {  debug("resetProperties");                                         }              
  if (io.kickerStart.click())          {  debug("kickerStart");     io.kickPermanent.set(true);             }          
  if (io.kickerStop.click())           {  debug("kickerStop");      io.kickPermanent.set(false);            }          
  if (io.shiftStart.click())           {
    debug(us.frontLeft());
    debug(us.left());
    debug(us.back());
    debug(us.right());
    debug(us.frontRight());
  }          
  if (io.shiftStop.click())            {  debug("shiftStop");                                               }        
/*
  if (io.drivePower.outsidePeriod(400)) drive.brake(false);
  if (io.driveEnabled.falling()) drive.brake(false);
  if (io.driveEnabled.off() && io.driveEnabled.outsidePeriod(100)) drive.brake(false);
*/

  updateStates();
// updateRating();
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

