#include "include.h"

void setup() {
  setupWatchdog();
  initUART();
  initDebug();
  initI2C();
  initEEPROM();
  initStates();
  io.battery.setLimits(true, true); // UGLY: zwinge den Akkuzustand auf verbunden

  light.init();
  initPui();
  camera.init();
  orientation.init();
  us.init();
  reflexion.init();
  // createCrashlog();
  // restoreSession();
  setupDone();
  digitalWrite(io.kick.getPin(), LOW);

  /*****************************************************/
  io.state.startDebug();
  // io.drivePower.startDebug();
  // io.stateDirection.startDebug();
  /*****************************************************/
}

void loop()
{
  prepareDebug(); // bereite debug nachrichten vor

  loopWatchdog();

  // debug(io.indRight.get());
  // debugln(io.indRight.getState());
  // io.indRight.setState(FALLING);

  // debug(io.indRight.get());
  // debugln(io.indRight.getState());

  io.update();

  // debug(io.indRight.get());
  // debugln(io.indRight.getState());

  reflexion.update();
  line.update();

  digitalWrite(io.buzzer.getPin(), false);
  digitalWrite(io.speaker.getPin(), false);

  if (io.hasBall.on())
    kick();

  if (orientation.onDemand())
    orientation.update();
  if (camera.onDemand())
    camera.frame();
  if (us.onDemand())
    us.update();

  if (io.selectMenu.click())
    debug(F("selectMenu"));
  if (io.testKick.click())
    kick();
  if (io.compassCalibration.click())
  {
    io.headingOffset.set(io.zOrientation.get());
    EEPROM.write(0, io.headingOffset.left());     // speichere Vorzeichen
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
  if (io.shiftStart.click())           {  
    debug(format(us.left(), 3, 3));
    debug(format(us.left2(), 3, 3));
    debug(format(us.left3(), 3, 3));
    debug(F("<>"));
    debug(format(us.right(), 3, 3));
    debug(format(us.right2(), 3, 3));
    debug(format(us.right3(), 3, 3));
  }          
  if (io.shiftStop.click())            {  debug(F("shiftShop"));                                               }        

  if (io.record.click())
    debug(F("record"));
  if (io.resetProperties.click())
    debug(F("resetProperties"));
  if (io.kickerStart.click())
  {
    debug(F("kickerStart"));
    io.kickPermanent.set(true);
  }
  if (io.kickerStop.click())
  {
    debug(F("kickerStop"));
    io.kickPermanent.set(false);
  }
  if (io.shiftStart.click())
  {
  }
  if (io.shiftStop.click())
    reflexion.calibrate();

  updateStates();
  // updateRating();
  updateKick();
  //updateAnimation();

  //calibrateGoal();
  //calibrateLightBeam();
  //calibrateLine();
  //drive.prepare();
  if (io.onLine.off())
    drive.update();
  else
    drive.drive(io.lineAngle.get() + 180, SPEED_LINE);
  drive.execute();
  if (light.onDemand())
    light.light();
  //bluetoth();
}
