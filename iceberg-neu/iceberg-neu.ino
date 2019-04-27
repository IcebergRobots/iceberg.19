//**********************************************
// ___  _____  _____  ____   _____  _____   _____
//  |   |      |____  |___]  |____  |____]  |  ___
// _|_  |____  |____  |___]  |____  |  \_   |____|
// _____   _____   ____    _____   _______  ______
// |____]  |    |  |___]   |    |     |     |_____
// |  \_   |____|  |___]   |____|     |     ______| 
// 
// Wir ham die Icebergs ... so gern!
//**********************************************

#include "include.h"
#include "HardwareSerial.h"

Camera cam;

void setup()
{
  initUART();
  initI2C();
  initEEPROM();
  initStates();
  

}

void loop()
{
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

  if (io.selectMenu.click()){}
  if (io.testKick.click())
    kick();
  if (io.compassCalibration.click())
  {
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
    io.pause = false;
  if (io.stop.click())
    io.pause = true;

  if (io.shiftStart.click())
  {}
  if (io.shiftStop.click())
  {}

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
