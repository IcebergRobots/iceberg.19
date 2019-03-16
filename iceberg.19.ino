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

  io.update();

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

  if (io.decreasePage.click())         {  /*d.changePage(-1);  */                                           }
  if (io.increasePage.click())         {  /*d.changePage(1);   */                                           }
  if (io.selectPage.click())           {  remoteControled = !remoteControled;                 }
  if (io.decreaseMenu.click())         {  /*d.scroll(-1);      */                                           }
  if (io.increaseMenu.click())         {  /*d.scroll(1);       */                                           }
  if (io.selectMenu.click())           {  debug(F("selectMenu"));                                           }
  if (io.testKick.click())             {  kick();                                                           }
  if (io.compassCalibration.click())   {
    io.headingOffset.set(io.zOrientation.get());
    EEPROM.write(0, io.headingOffset.left());     // speichere Vorzeichen
    EEPROM.write(1, abs(io.headingOffset.get())); // speichere Winkel
  }
  if (io.animation.click())
    io.animationEnabled.set(!io.animationEnabled.get());
  if (io.lineCalibration.click())
    BOTTOM_SERIAL.write(42);
  if (io.ballTouchCalibration.click())
    reflexion.calibrate();
  if (io.start.click())
    io.pause.set(false);
  if (io.stop.click())
    io.pause.set(true);

  if (io.shiftStart.click())
  {
    debug(format(us.left(), 3, 3));
    debug(format(us.left2(), 3, 3));
    debug(format(us.left3(), 3, 3));
    debug(F("<>"));
    debug(format(us.right(), 3, 3));
    debug(format(us.right2(), 3, 3));
    debug(format(us.right3(), 3, 3));
  }
  if (io.shiftStop.click())
  {
  }

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
  if (io.onLine.off())
    drive.update();
  else
    drive.drive(io.lineAngle.get() + 180, SPEED_LINE);
  drive.execute();
  }
  if (light.onDemand())
    light.light();
  //bluetoth();
  
}
