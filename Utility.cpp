#include "Utility.h"

void initUART() {
  DEBUG_SERIAL.begin(DEBUG_BAUDRATE);
  BLUETOOTH_SERIAL.begin(BLUETOOTH_BAUDRATE);
  BLACKBOX_SERIAL.begin(BLACKBOX_BAUDRATE);
}

void initI2C() {
  beginSegment("i2c");
  I2c.begin();
  //I2c.scan();
  endSegment();
}

void setupWatchdog() {
  if(WATCHDOG_SETUP != WDTO_OFF) wdt_enable(WATCHDOG_SETUP);
}

void loopWatchdog() {
  if(WATCHDOG_LOOP != WDTO_OFF) wdt_enable(WATCHDOG_LOOP);
}

void initDebug() {
  debugFunction = printDebug;
  beginSegmentFunction = printBeginSegment;
  endSegmentFunction = printEndSegment;
  io.hasDebugHead.set(true);
  String str = "";
  if (!DEBUG_ENABLED) str += "\nUSB DEBUG DEACTIVATED!";
  else {
    str += "\nICEBERG ROBOTS 2019\n";
    str += "Anton Pusch, Finn Harms, Ibo Becker, Oona Kintscher";
  }
  DEBUG_SERIAL.println(str);
}

void setupDone() {
  String str = "=" + String(millis()) + "\n";
  for (int i = 0; i < 60; i++) str += "=";
  debug(str);
  io.runtime.set();
}

/*****************************************************
  Berechne alle Statuswerte und Zustände
*****************************************************/
void calculateStates() {
}

void prepareDebug() {
  io.hasDebugHead.set(false);
  if (DEBUG_LOOP) debug();
}


void updateStates() {
  io.hasBall.set(io.ballTouch.get() > 30/*lightBarrierTriggerLevel*/);
  io.ballLeft.set(io.ball.left(BALL_CENTER_TOLERANCE));
  io.ballRight.set(io.ball.right(BALL_CENTER_TOLERANCE));
  io.ballCenter.set(io.ball.center(BALL_CENTER_TOLERANCE));

  // erkenne Hochheben
  //dof.accelGetOrientation(&accel_event, &orientation);
  //io.flat.set(!((orientation.roll > 30 && abs(orientation.pitch) < 20) || accel_event.acceleration.z < 7));
}

void printDebug(String str, bool space) {
  if (DEBUG_ENABLED && io.turbo.off()) {
    if (io.hasDebugHead.on() && space) str = " " + str;
    if (io.hasDebugHead.off()) {
      io.hasDebugHead.set(true);
      str = "\n" + format("t" + io.runtime.str(), 6) + " " + str;
      io.runtime.set();
    }
    DEBUG_SERIAL.print(str);
  }
}

void printBeginSegment(String name) {
  if(io.runtime.never() || DEBUG_SEGMENT) { // if in setup or DEBUG_SEGMENT
    debug(name + "{");
    io.segment.set();
  }
}
void printEndSegment() {
  if(io.runtime.never() || DEBUG_SEGMENT) debug("}"+ io.segment.str(), false); // if in setup or DEBUG_SEGMENT
}