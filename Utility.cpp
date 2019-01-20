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
  if(WATCHDOG) wdt_enable(WATCHDOG_SETUP);
}

void loopWatchdog() {
  if(WATCHDOG) wdt_enable(WATCHDOG_LOOP);
}

void initDebug() {
  String str = "";
  if (!DEBUG) str += "\nUSB DEBUG DEACTIVATED!";
  else {
    str += "\nICEBERG ROBOTS 2019\n";
    str += "Anton Pusch, Finn Harms, Ibo Becker, Oona Kintscher";
  }
  DEBUG_SERIAL.println(str);
}

void setupDone() {
  String str = "\n";
  for (int i = 0; i < 60; i++) str += "=";
  debug(str);
}

/*****************************************************
  Berechne alle Statuswerte und Zustände
*****************************************************/
void calculateStates() {
}

void prepareDebug() {
  hasDebugHead = false;
  if (DEBUG_LOOP) debug();
}


void updateStates() {
  //io.lifted.set(                        millis() - flatTimer > FLAT_DURATION             );
  //io.onLine.set(                        millis() - lineTimer < LINE_DURATION             );
  //io.isHeadstart.set(                     millis() - headstartTimer < HEADSTART_DURATION   );
  //io.isDodge.set(                         millis() - dodgeTimer < DODGE_DURATION           );
  //io.hasBall.set(    analogRead(LIGHT_BARRIER) > lightBarrierTriggerLevel;               );
  io.seeBall.set(    io.lifted.off() && millis() - seeBallTimer < 100                    );
  io.seeGoal.set(    io.lifted.off() && millis() - seeGoalTimer < 500                    );
  io.closeBall.set(  io.seeBall.on() && millis() - closeBallTimer < 500                  );

  // erkenne Hochheben
  //dof.accelGetOrientation(&accel_event, &orientation);
  //if (!((orientation.roll > 30 && abs(orientation.pitch) < 20) || accel_event.acceleration.z < 7)) flatTimer = millis();
}