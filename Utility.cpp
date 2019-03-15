#include "Utility.h"

void kick() {
  if (io.kickActive.period() > 600) io.kickActive.set();
}

void initUART() {
  DEBUG_SERIAL.begin(DEBUG_BAUDRATE);
  BLUETOOTH_SERIAL.begin(BLUETOOTH_BAUDRATE);
  BLACKBOX_SERIAL.begin(BLACKBOX_BAUDRATE);
  BOTTOM_SERIAL.begin(BOTTOM_BAUDRATE);
}

void initI2C() {
  beginSegment(F("i2c"));
  // I2c.begin();
  // I2c.scan();
  Wire.begin();
  endSegment();
}

void initInterrupt(){
  attachInterrupt(digitalPinToInterrupt(io.lineInterrupt.getPin()), requestLineFetch, RISING);
}

void requestLineFetch() {
  isLineFetchRequest = true;
}

void setupWatchdog() {
  if(WATCHDOG_SETUP != WDTO_OFF) wdt_enable(WATCHDOG_SETUP);
  else wdt_disable();
}

void loopWatchdog() {
  if(WATCHDOG_LOOP != WDTO_OFF) wdt_enable(WATCHDOG_LOOP);
  else wdt_disable();
}

void initDebug() {
  debugFunction = printDebug;
  beginSegmentFunction = printBeginSegment;
  endSegmentFunction = printEndSegment;
  io.hasDebugHead.set(true);
  DEBUG_SERIAL.println();
  DEBUG_SERIAL.println();
  if (!DEBUG_ENABLED) DEBUG_SERIAL.println(F("USB DEBUG DEACTIVATED!"));
  else {
    DEBUG_SERIAL.println(F("ICEBERG ROBOTS 2019"));
    DEBUG_SERIAL.println(F("Anton Pusch, Finn Harms, Ibo Becker, Oona Kintscher"));
  }
}

void setupDone() {
  debugln("=" + String(millis()));
  for (int i = 0; i < 9; i++) debug(F("======"), false);
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

void initStates() {
  io.driveEnabled.set(true);
  io.batteryVoltmeter.update();
  io.battery.set(io.batteryVoltmeter.get() >= BATTERY_MIN_VOLTAGE);
  io.pause.set(true);
}

void updateStates() {
  if (io.hasBall.on() && io.seeBall.off()) { // wenn wir den Ball besitzen, erzeuge einen Kamerablock falls nicht vorhanden
    io.seeBall.set();
    io.ball.set(0); // Ball liegt gerade vor uns
  }

  // erkenne die Lage des Balls
  io.seeBallLeft.set(io.ball.left(BALL_CENTER_TOLERANCE));
  io.seeBallRight.set(io.ball.right(BALL_CENTER_TOLERANCE));
  io.seeBallCenter.set(io.ball.center(BALL_CENTER_TOLERANCE));

  // io.onLine.set(io.lineAvoid.on() || io.lineDetected.on());

  io.batteryVoltage.set(io.batteryVoltmeter.get() * 0.1249);
  io.battery.set(io.batteryVoltmeter.get() >= BATTERY_MIN_VOLTAGE);
  io.flat.set(true);
  io.driveEnabled.set(io.pause.off() && io.motor.on());
  // erkenne Hochheben
  // dof.accelGetOrientation(&accel_event, &orientation);
  // io.flat.set(!((orientation.roll > 30 && abs(orientation.pitch) < 20) || accel_event.acceleration.z < 7));
}

void initEEPROM() {
  if (EEPROM.read(0) == 0) io.headingOffset.set(EEPROM.read(1));
  else io.headingOffset.set(-EEPROM.read(1));
}

void printDebug(String str, bool space) {
  if (DEBUG_ENABLED && io.turbo.off()) {
    if (io.segment.is(SEGMENT_EMPTY)) {
      io.segment.muteSet(SEGMENT_FILLED);
      space = false;
    }
    if (io.hasDebugHead.on() && space) str = " " + str;
    if (io.hasDebugHead.off()) {
      io.hasDebugHead.set(true);
      DEBUG_SERIAL.println();
      DEBUG_SERIAL.print(format("t" + io.runtime.str(), 6));
      DEBUG_SERIAL.print(F(" "));
      if (DEBUG_MOTOR) {
        DEBUG_SERIAL.print(format(io.driveEnabled.on() * io.drivePower.get(), 3, 3));
        DEBUG_SERIAL.print(F("*"));
        DEBUG_SERIAL.print(format(circulate(io.driveAngle.get(), -179, 180), 4, 4, true));
        DEBUG_SERIAL.print(F(" "));
      }
      if (DEBUG_INFO) {
        DEBUG_SERIAL.print(format(us.left(), 3, 3));
        DEBUG_SERIAL.print(F("<>"));
        DEBUG_SERIAL.print(format(us.right(), 3, 3));
        DEBUG_SERIAL.print(F(" "));
      }
      io.runtime.set();
    }
    DEBUG_SERIAL.print(str);
  }
}

void printBeginSegment(String name) {
  if (io.runtime.never() || DEBUG_SEGMENT) { // if in setup or DEBUG_SEGMENT
    if (io.segment.on()) endSegment();
    debug(name + "{");
    io.segment.set(SEGMENT_EMPTY); // start timer
  }
}
void printEndSegment() {
  if (io.runtime.never() || DEBUG_SEGMENT) {
    if (io.segment.on()) {
      debug("}"+ io.segment.periodStr(), false); // if in setup or DEBUG_SEGMENT
      io.segment.set(0);
    }
  }
}

void initPui() {
  if (io.battery.on()) {
    beginSegment(F("pui"));
    pui.begin();
    endSegment();
  } else debug(F("-pui"));
}

void updateKick(){
  if(io.kickActive.get())
    debug("KickActive");
  digitalWrite(io.kick.getPin(), io.kickActive.get());
  digitalWrite(io.buzzer.getPin(), io.kickActive.get());
}