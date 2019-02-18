#include "IO.h"

/*********************************************************************
  Constructor
*********************************************************************/
IO::IO() {}

void IO::update() {
  if (DEBUG_LOOP) beginSegment("io");

  for(int i = 0; i < objects<Value>(); i++) {
    Value *v = objects<Value>(i);
    switch (v->getElementType()) {
      case VALUE:
        v->update();
        break;
    
      case TIMER:
        Timer *t = v;
        t->update();
        break;

      default:
        break;
    }
  }

  endSegment();
  beginSegment();

  temperaturePcb.update();
  brightnessPcb.update();
  batteryVoltage.update();
  temperatureMd.update();
  buzzer.update();

  // Ausgabe
  indFront.update();
  speaker.update();
  indLeft.update();
  indRight.update();
  indRgb.update();
  indHearbeat.update();

  // Bluetooth
  bluetoothTx.update();
  bluetoothRx.update();

  // Bodensensor
  lineInterrupt.update();
  lineLight.update();
  lineTx.update();
  lineRx.update();

  // Freigelegte Pins
  test1.update();
  test2.update();
  test3.update();
  jumper1.update();
  jumper2.update();
  jumper3.update();
  jumper4.update();
  jumper5.update();
  jumper6.update();

  // I2C
  scl.update();
  sda.update();

  // Positionslichter
  navigationAntennaB.update();
  navigationAntennaA.update();
  navigationAntennaC.update();
  navigationAntennaD.update();
  navigationLight.update();

  // Lichtschranke
  ballLight.update();
  ballTouch.update();

  // Logger
  loggerTx.update();
  loggerRx.update();

  // Logic Analyser
  loggerTrigger.update();

  // Motortreiber
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

  // PUI-Anschluss
  puiLight.update();
  puiInterrupt.update();
  poti.update();
  headstart.update();
  motor.update();
  bluetooth.update();
  kicker.update();
  bottom.update();
  turbo.update();


  // Schuss-Elektronik
  kick.update();

  // Servo
  cameraServo.update();

  // SPI 
  spiClk.update();
  spiCs.update();
  spiMiso.update();
  spiMosi.update();

  // USB 
  usbTx.update();
  usbRx.update();

  endSegment();
  beginSegment();

  // PUI: keys and levers
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

  // PUI: shortcuts
  record.update();
  resetProperties.update();
  kickerStart.update();
  kickerStop.update();
  shiftStart.update();
  shiftStop.update();

  if (DEBUG_LOOP) endSegment();
}

IO io;