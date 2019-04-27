#include "Utility.h"

readCamera()

void kick()
{
  if (KICKER_ENABLED && io.kicker.on() && io.kickActive.outsidePeriod(600))
    io.kickActive.now();
}

/*****************************************************
  initialisiere alle seriellen Schnittstellen
  - lege die Baudraten fest
*****************************************************/
void initUART()
{
  BLUETOOTH_SERIAL.begin(BLUETOOTH_BAUDRATE);
  BOTTOM_SERIAL.begin(BOTTOM_BAUDRATE);
}

/*****************************************************
  initialisiere den IC2 Bus
*****************************************************/
void initI2C()
{
  beginSegment(F("i2c"));
  // I2c.begin();
  // I2c.scan();
  Wire.begin();
  endSegment();
}

/*****************************************************
  (de)aktiviere den Einfrier-Timeout der Setup
*****************************************************/
void setupWatchdog()
{
  if (WATCHDOG_SETUP != WDTO_OFF)
    wdt_enable(WATCHDOG_SETUP);
  else
    wdt_disable();
}

/*****************************************************
  (de)aktiviere den Einfrier-Timeout der Loop
*****************************************************/
void loopWatchdog()
{
  if (WATCHDOG_LOOP != WDTO_OFF)
    wdt_enable(WATCHDOG_LOOP);
  else
    wdt_disable();
}

void setupDone()
{
  io.runtime.now();
}

/*****************************************************
  setzte gegebenfalls Startwerte für globale Variablen 
*****************************************************/
void initStates()
{
  io.driveEnabled.set(true); // aktiviere das Fahrgestell
  io.pause=true;        // verhindere, dass die Roboter sofort losfahren

  io.batteryVoltmeter.update();                                     // miss die Akkuspannung
  io.battery.set(io.batteryVoltmeter.get() >= BATTERY_MIN_VOLTAGE); // bestimme, welche Klassen initialisieren sollen
}

/*****************************************************
  berechne die globalen Eigenschaften 
*****************************************************/
void updateStates()
{
  if (io.hasBall.on() && io.seeBall.off())
  { // wenn wir den Ball besitzen, erzeuge einen Kamerablock falls nicht vorhanden
    io.seeBall.now();
    io.ball.set(0); // Ball liegt gerade vor uns
  }

  // erkenne die Lage des Balls
  if (io.ball.left(BALL_CENTER_TOLERANCE))
    io.seeBallLeft.now();
  if (io.ball.right(BALL_CENTER_TOLERANCE))
    io.seeBallRight.now();
  if (io.ball.center(BALL_CENTER_TOLERANCE))
    io.seeBallCenter.now();

  io.batteryVoltage.set(io.batteryVoltmeter.get() * 0.1249);
  io.battery.set(io.batteryVoltmeter.get() >= BATTERY_MIN_VOLTAGE);
  io.flat.now();
  io.driveEnabled.set(!io.pause && io.motor.on());
  // erkenne Hochheben
  // dof.accelGetOrientation(&accel_event, &orientation);
  // io.flat.set(!((orientation.roll > 30 && abs(orientation.pitch) < 20) || accel_event.acceleration.z < 7));
}

void initEEPROM()
{
  if (EEPROM.read(0) == 0)
    io.headingOffset.set(EEPROM.read(1));
  else
    io.headingOffset.set(-EEPROM.read(1));
}

void printBeginSegment(String name)
{
  if (io.runtime.never())
  { 
    if (io.segment.on())
      endSegment();
    io.segment.set(SEGMENT_EMPTY); // start timer
  }
}
void printEndSegment()
{
  if (io.runtime.never())
  {
    if (io.segment.on())
    {
      io.segment.set(0);
    }
  }
}

void initPui()
{
  if (io.battery.on())
  {
    beginSegment(F("pui"));
    pui.begin();
    endSegment();
  }
}

void updateKick()
{
  digitalWrite(io.kick.getPin(), io.kickActive.on());
  digitalWrite(io.buzzer.getPin(), io.kickActive.on());
}