#include "include.h"

bool remoteControled = true;

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
  camera.init();
  orientation.init();
  us.init();
  reflexion.init();
  // createCrashlog();
  // restoreSession();
  setupDone();

  /*****************************************************/
  // io.state.startDebug();
  // io.drivePower.startDebug();
  // io.stateDirection.startDebug();
  // digitalWrite(io.kick.getPin(), LOW);
  /*****************************************************/
}

void loop() {
  prepareDebug();  // bereite debug nachrichten vor
  
  loopWatchdog();

  io.update();
  reflexion.update();

  digitalWrite(io.buzzer.getPin(), false);
  digitalWrite(io.speaker.getPin(), false);

  if(io.hasBall.on())
    kick();

  if (orientation.onDemand()) orientation.update();
  if (camera.onDemand()) camera.frame();
  if (us.onDemand()) us.update();

  if (io.decreasePage.click())         {  /*d.changePage(-1);  */                                           }
  if (io.increasePage.click())         {  /*d.changePage(1);   */                                           }
  if (io.selectPage.click())           {  remoteControled = !remoteControled;                 }
  if (io.decreaseMenu.click())         {  /*d.scroll(-1);      */                                           }
  if (io.increaseMenu.click())         {  /*d.scroll(1);       */                                           }
  if (io.selectMenu.click())           {  debug(F("selectMenu"));                                           }
  if (io.testKick.click())             {  kick();                                                           }
  if (io.compassCalibration.click())   {
    io.headingOffset.set(io.zOrientation.get());
    EEPROM.write(0, io.headingOffset.left());  // speichere Vorzeichen
    EEPROM.write(1, abs(io.headingOffset.get())); // speichere Winkel
  }
  if (io.animation.click())            {  io.animationEnabled.set( ! io.animationEnabled.get() );              }
  if (io.lineCalibration.click())      {  BOTTOM_SERIAL.write(42);                                             }
  if (io.ballTouchCalibration.click()) {  reflexion.calibrate();                                               }
  if (io.start.click())                {  io.pause.set(false);                                                 }
  if (io.stop.click())                 {  io.pause.set(true);                                                  }
  
  if (io.record.click())               {  debug(F("record"));                                                  }      
  if (io.resetProperties.click())      {  debug(F("resetProperties"));                                         }              
  if (io.kickerStart.click())          {  debug(F("kickerStart"));     io.kickPermanent.set(true);             }          
  if (io.kickerStop.click())           {  debug(F("kickerStop"));      io.kickPermanent.set(false);            }          
  if (io.shiftStart.click())           {  debug(F("shiftStart"));                                              }          
  if (io.shiftStop.click())            {  debug(F("shiftShop"));                                               }        
/*
  if (io.drivePower.outsidePeriod(400)) drive.brake(false);
  if (io.driveEnabled.falling()) drive.brake(false);
  if (io.driveEnabled.off() && io.driveEnabled.outsidePeriod(100)) drive.brake(false);
*/

  updateStates();
// updateRating();
  updateKick();
  //updateAnimation();

  //calibrateGoal();
  //calibrateLightBeam();
  //calibrateLine();
  //drive.prepare();
  digitalWrite(io.indLeft.getPin(), remoteControled*255);
  digitalWrite(io.indRight.getPin(), remoteControled*255);

  if(remoteControled){
    checkRemote();
  }else{
    //drive.update();
    //drive.execute();
  }
  if (light.onDemand()) light.light();
  //bluetoth();
  
}

