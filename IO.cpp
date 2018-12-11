#include "IO.h"

/*********************************************************************
- Konstruktor
*********************************************************************/
IO::IO() {}

void IO::update() {
  temperaturePcb.update();
  brightnessPcb.update();
  batteryVoltage.update();
  temperatureMd.update();
  buzzer.update();
  indFront.update();
  speaker.update();
  indLeft.update();
  indRight.update();
  indRgb.update();
  indHearbeat.update();
  bluetoothTx.update();
  bluetoothRx.update();
  lineInterrupt.update();
  lineLight.update();
  lineTx.update();
  lineRx.update();
  test1.update();
  test2.update();
  test3.update();
  jumper1.update();
  jumper2.update();
  jumper3.update();
  jumper4.update();
  jumper5.update();
  jumper6.update();
  scl.update();
  sda.update();
  navigationAntennaB.update();
  navigationAntennaA.update();
  navigationAntennaC.update();
  navigationAntennaD.update();
  navigationLight.update();
  lightBeamTx.update();
  lightBeamRx.update();
  loggerTx.update();
  loggerRx.update();
  loggerTrigger.update();
  m0Speed.update();
  m0Dir1.update();
  m0Dir2.update();
  m0Current.update();
  m1Speed.update();
  m1Dir1.update();
  m1Dir2.update();
  m1Current.update();
  m2Speed.update();
  m2Dir1.update();
  m2Dir2.update();
  m2Current.update();
  m3Speed.update();
  m3Dir1.update();
  m3Dir2.update();
  m3Current.update();
  puiLight.update();
  puiInterrupt.update();
  puiPoti.update();
  kick.update();
  cameraServo.update();
  spiClk.update();
  spiCs.update();
  spiMiso.update();
  spiMosi.update();
  usbTx.update();
  usbRx.update();

  decreasePage.update();
  increasePage.update();
  selectPage.update();
  decreaseMenu.update();
  increaseMenu.update();
  selectMenu.update();
  testKick.update();
  compassCalibration.update();
  animation.update();
  lineCalibration.update();
  lightBeamCalibration.update();
  start.update();
  stop.update();
  headstart.update();
  motor.update();
  bluetooth.update();
  kicker.update();
  bottom.update();
  debug.update();

  record.update();
  resetProperties.update();
  kickerStart.update();
  kickerStop.update();
}

IO io = IO();