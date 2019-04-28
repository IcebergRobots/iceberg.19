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

void setup()
{ 
  setupWatchdog();
  initUART();
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

  setupDone();
  digitalWrite(io.kick.getPin(), LOW);
}

void loop()
{
  //loopWatchdog(); 
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

  handleKeyEvents();
  updateStates();
  // updateRating();
  updateKick();

  if(io.driveEnabled.falling()){
    drive.brake();
  }

  drive.update();

  /*if (io.onLine.off())
    drive.update();
  else
    drive.drive(io.lineAngle.get() + 180, SPEED_LINE);
  drive.execute();*/

  if (light.onDemand())
    light.light();
}
