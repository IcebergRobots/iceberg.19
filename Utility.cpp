#include "Utility.h"

void checkRemote(){
  if(io.lastRemoteSignal.off()){
    drive.drive(0,0);
    drive.execute();
  }
  while(BLUETOOTH_SERIAL.available()>=20){
    BLUETOOTH_SERIAL.read();
  }

  if(BLUETOOTH_SERIAL.available()>=5){
    if(BLUETOOTH_SERIAL.read() != 255){
      checkRemote();
      return;
    }

    byte checksum     = BLUETOOTH_SERIAL.read();
    int  angle        = BLUETOOTH_SERIAL.read();
    int power        = BLUETOOTH_SERIAL.read();
    byte activateKick = BLUETOOTH_SERIAL.read();

    

    if(checksum != (angle+power+activateKick)%254+1) 
      return;

    angle = 360 - (angle * 2);
    int x = map(io.poti.get(), 0, 1023, 0, 255);
    power = map(power < 100 ? 0 : power, 100, 255, 0, x);
    if(power < 0)
      power = 0;
    activateKick = activateKick == 1;

  


    if(activateKick){
      kick();
    }

    int rot = drive.face(0);
    drive.drive(angle, power, rot);
    drive.execute();
    io.lastRemoteSignal.now();
  }
}
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
  DEBUG_SERIAL.begin(DEBUG_BAUDRATE);
  BLUETOOTH_SERIAL.begin(BLUETOOTH_BAUDRATE);
  BLACKBOX_SERIAL.begin(BLACKBOX_BAUDRATE);
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

/*****************************************************
  initialisiere den USB-Debug zum PC
  - sende einen Infotext als Anfang der USB-Kommunikation
*****************************************************/
void initDebug()
{
  // einige Methoden benutzen das io-Objekt und müssen daher nachträglich mittels Methodenpointer initialisiert werden
  debugFunction = printDebug;               // setzte den Methodenpointer zum Debuggen
  beginSegmentFunction = printBeginSegment; // setze den Methodenpointer zum Starten eines Codesegmentes
  endSegmentFunction = printEndSegment;     // setzte den Methodenpointer zum Beenden eines Codesegmentes

  io.hasDebugHead.set(true); // verhindere, dass der Zeitstempel an den Anfang des Infotextes gedruckt wird
  DEBUG_SERIAL.println();
  DEBUG_SERIAL.println(); // lasse eine Zeile frei, damit der Reset besser erkennbar ist
  if (!DEBUG_ENABLED)
    DEBUG_SERIAL.println(F("USB DEBUG DEACTIVATED!"));
  else
  {
    DEBUG_SERIAL.println(F("ICEBERG ROBOTS 2019"));
    DEBUG_SERIAL.println(F("Anton Pusch, Finn Harms, Ibo Becker, Oona Kintscher"));
  }
}

/*****************************************************
  initialisiere den USB-Debug zum PC
  - sende einen Infotext als Anfang der USB-Kommunikation
*****************************************************/
void setupDone()
{
  debugln("=" + String(millis()));
  for (int i = 0; i < 9; i++)
    debug(F("======"), false);
  io.runtime.now();
}

/*****************************************************
  bereite den Zeitstempel für das Debugging vor
  - wenn DEBUG_LOOP gesetzt, drucke den Zeitstempel
*****************************************************/
void prepareDebug()
{
  io.hasDebugHead.set(false); // aktiviere den Zeitstempel
  if (DEBUG_LOOP)
    debug(); // drucke den Zeitstempel
}

/*****************************************************
  setzte gegebenfalls Startwerte für globale Variablen 
*****************************************************/
void initStates()
{
  io.driveEnabled.set(true); // aktiviere das Fahrgestell
  io.pause.set(true);        // verhindere, dass die Roboter sofort losfahren

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
  io.driveEnabled.set(io.pause.off() && io.motor.on());
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

void printDebug(String str, bool space)
{
  if (DEBUG_ENABLED && io.turbo.off())
  {
    if (io.segment.is(SEGMENT_EMPTY))
    {
      io.segment.setWithoutEvent(SEGMENT_FILLED);
      space = false;
    }
    if (io.hasDebugHead.on() && space)
      str = " " + str;
    if (io.hasDebugHead.off())
    {
      io.hasDebugHead.set(true);
      DEBUG_SERIAL.println();
      DEBUG_SERIAL.print(format("t" + io.runtime.str(), 6));
      DEBUG_SERIAL.print(F(" "));
      if (DEBUG_MOTOR)
      {
        DEBUG_SERIAL.print(format(io.driveEnabled.on() * io.drivePower.get(), 3, 3));
        DEBUG_SERIAL.print(F("*"));
        DEBUG_SERIAL.print(format(circulate(io.driveAngle.get(), -179, 180), 4, 4, true));
        DEBUG_SERIAL.print(F(" "));
      }
      if (DEBUG_INFO)
      {
      }
      io.runtime.now();
    }
    DEBUG_SERIAL.print(str);
  }
}

void printBeginSegment(String name)
{
  if (io.runtime.never() || DEBUG_SEGMENT)
  { // if in setup or DEBUG_SEGMENT
    if (io.segment.on())
      endSegment();
    debug(name + "{");
    io.segment.set(SEGMENT_EMPTY); // start timer
  }
}
void printEndSegment()
{
  if (io.runtime.never() || DEBUG_SEGMENT)
  {
    if (io.segment.on())
    {
      debug("}" + io.segment.str(), false); // if in setup or DEBUG_SEGMENT
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
  else
    debug(F("-pui"));
}

void updateKick()
{
  digitalWrite(io.kick.getPin(), io.kickActive.on());
  digitalWrite(io.buzzer.getPin(), io.kickActive.on());
}