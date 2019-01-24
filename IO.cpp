#include "IO.h"

/*********************************************************************
  Constructor
*********************************************************************/
IO::IO() {}

void IO::update() {
  if (DEBUG_LOOP) beginSegment("io");
  
  // pins
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
  ballLight.update();
  ballTouch.update();
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
  poti.update();
  kick.update();
  cameraServo.update();
  spiClk.update();
  spiCs.update();
  spiMiso.update();
  spiMosi.update();
  usbTx.update();
  usbRx.update();
  
  // keys
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
  ballTouchCalibration.update();
  start.update();
  stop.update();
  headstart.update();
  motor.update();
  bluetooth.update();
  kicker.update();
  bottom.update();
  turbo.update();

  // shortcuts
  record.update();
  resetProperties.update();
  kickerStart.update();
  kickerStop.update();
  shiftStart.update();
  shiftStop.update();

  // timers
  flat.update();
  onLine.update();
  isHeadstart.update();
  isDodge.update();
  hasBall.update();
  segment.update();
  runtime.update();
  seeBall.update();
  seeGoal.update();
  closeBall.update();
  drift.update();
  ballLeft.update();
  ballRight.update();
  ballCenter.update();
  cameraResponse.update();

  // values
  striker.update();
  state.update();
  stateDirection.update();

  driveAngle.update();
  drivePower.update();
  driveRotation.update();
  driveEnabled.update();

  ball.update();
  ballWidth.update();
  ballArea.update();
  goal.update();
  goalWidth.update();
  goalArea.update();
  
  hasDebugHead.update();

  if (DEBUG_LOOP) endSegment();
}

IO io;