#include "Utility.h"

// Implementierung: OBJEKTE
extern Display d;
extern Player p;
extern Led led;
extern Mate mate;
extern Pilot m;
extern Ultrasonic us;
extern Input input;

extern struct bno055_euler myEulerData;	  //Structure to hold the Euler data
extern struct bno055_t compass;

void reset() {
  asm ("jmp 0");   // starte den Arduino neu
}

int shift(int &value, int min, int max) {
  max -= min;
  value = (max + (value - min % max)) % max + min; // wandle Drehposition in Zustand von 0 bis ROTARY_RANGE um
  return value;
}

void startSound() {
  //Fiepen, welches Programstart signalisiert
  for (int i = 10; i < 2000; i += 10) {
    tone(BUZZER, i);
    delay(1);
  }
  noTone(BUZZER);
}

/*****************************************************
  Berechne alle Statuswerte und Zustände
*****************************************************/
void calculateStates() {
  isLifted = millis() - flatTimer > 600;
  onLine = millis() - lineTimer < LINE_DURATION;
  isHeadstart = millis() - headstartTimer < HEADSTART_DURATION;
  isAvoidMate = millis() - avoidMateTimer < AVOID_MATE_DURATION;
  batVol = analogRead(BATT_VOLTAGE) * 0.124783;  // SPANNUNG MAL 10!
  if (batVol > VOLTAGE_MIN) {
    batState = 1; // ok
    if (m.getMotEn()) {
      if (batVol < VOLTAGE_MOTOR_CRIT) {
        batState = 3; // kritisch
      } else if (batVol < VOLTAGE_MOTOR_LOW) {
        batState = 2; // gering
      }
    } else {
      if (batVol < VOLTAGE_CRIT) {
        batState = 3; // kritisch
      } else if (batVol < VOLTAGE_LOW) {
        batState = 2; // gering
      }
    }
  } else {
    batState = 0; // no battery
  }
  silent = input.switch_debug;
  silent != silent;

  hasBall = analogRead(LIGHT_BARRIER) > lightBarrierTriggerLevel;
  seeBall = !isLifted && millis() - seeBallTimer < 100;
  seeGoal = !isLifted && millis() - seeGoalTimer < 500;
  seeEast = !isLifted && millis() - seeEastTimer < 500;
  seeWest = !isLifted && millis() - seeWestTimer < 500;
  closeBall = seeBall && millis() - closeBallTimer < 500;
  isDrift = millis() - driftTimer < 100;
  isHeadstart = millis() - headstartTimer < HEADSTART_DURATION;
  if (pixyResponseTimer > 0 && millis() - pixyResponseTimer < PIXY_RESPONSE_DURATION) {
    // Kamera war in den letzen 30 Sekunden bereits aktiv
    pixyState = 1;
  } else if (pixyResponseTimer > 0) {
    // Kamera war seit dem letzten Neustart bereits aktiv
    pixyState = 2;
  } else {
    // Kamera nicht angeschlossen
    pixyState = 3;
  }

  if (us.right() + us.left() >= COURT_WIDTH_FREE) penaltyFreeTimer = millis();
  isPenaltyFree = us.right() + us.left() >= COURT_WIDTH_FREE;

  // erkenne Hochheben
  //TODO
  //dof.accelGetOrientation(&accel_event, &orientation);
  //if (!((orientation.roll > 30 && abs(orientation.pitch) < 20) || accel_event.acceleration.z < 7)) flatTimer = millis();
}

/*****************************************************
  Sende einen Herzschlag mit Statusinformationen an den Partner

  Byte    Information   mögliche Zustände
  -----------------------------------------------------
  0       Pakettyps     Heartbeat(104)
  1       Status+Rolle  Aus(0+Status) / Torwart(1+Status) / Stürmer(2+Status)
  2       Score         Blind(0) / Bewertung(...)
*****************************************************/
void transmitHeartbeat() {
  rating();

  byte data[3];
  data[0] = 'h';
  if (!m.getMotEn()) data[1] = p.getState();
  else if (p.isKeeper()) data[1] = p.getState() + 10;
  else if (p.isRusher()) data[1] = p.getState() + 20;
  data[2] = score;
  mate.send(data, 3); // heartbeat
  bluetoothTimer = millis();
}

/*****************************************************
  Piloten konfigurieren
*****************************************************/
void setupMotor() {
  m.setAngle(70);

  m.setPins(0, FWD0, BWD0, PWM0, M0_CURR);
  m.setPins(1, FWD1, BWD1, PWM1, M1_CURR);
  m.setPins(2, FWD2, BWD2, PWM2, M2_CURR);
  m.setPins(3, FWD3, BWD3, PWM3, M3_CURR);
}

void avoidLine() {
  buzzerTone(100);
  while (BOTTOM_SERIAL.available() > 1) {
    BOTTOM_SERIAL.read();
  }
  if (BOTTOM_SERIAL.available() > 0) {
    lineDir = (BOTTOM_SERIAL.read() * 22.5) - 180;
    driveDirection = lineDir;
    m.drive(driveDirection, SPEED_LINE, 0);
    lineTimer = millis();
    headstartTimer = 0;
    /*if (drivePower > 200) {
      lineTimer = millis() + (2 * LINE_DURATION);
      } else if (drivePower > 100) {
      lineTimer = millis() + (1.5 * LINE_DURATION);
      } else {
      lineTimer = millis() + LINE_DURATION;
      }*/
    displayDebug = driveDirection;
  }


}

void handleStartStop(){
  //TODO: Bluetooth Start & Stop

  if(input.button_start){
    m.setMotEn(true);
  }

  if(input.button_stop){
    m.setMotEn(false);
  }

  if(!(bool)(input.switch_motor)){
    m.setMotEn(false);
  }
}

void handleBluetooth(){
  byte command = mate.receive();
  if (DEBUG_BLUETOOTH && command != 255 && command != 'h') debug(String((char)command));
  switch (command) {
    case 'h': // heartbeat
      if (mate.getMotEn()) {
        start = true;
        led.cancel();
        if (!wasStartButton && input.switch_headstart && !m.getMotEn()) headstartTimer = millis();
      }
      break;

    case 'b': // brake
      start = false;
      m.brake(true);
      break;

    case 'e': // avoid mate to east
      avoidMateTimer = millis();
      driveDirection = 100;
      driveState = "> mate";
      break;

    case 'w': // avoid mate to west
      avoidMateTimer = millis();
      driveDirection = -100;
      driveState = "< mate";
      break;
  }

  if (mate.timeout() || !mate.getMotEn()) p.setKeeper(true);
  else if (isTypeA) {
    if (seeBall && !mate.getScore()) p.setRusher(false);
    if (!seeBall && mate.getScore()) p.setKeeper(false);
    if (seeBall && mate.getScore() && abs(score - mate.getScore()) >= 40) {
      if (score > mate.getScore()) p.setRusher(false);
      if (score < mate.getScore()) p.setKeeper(false);
    }
  } else {
    if (mate.isKeeper()) p.setRusher(true);
    if (mate.isRusher()) p.setKeeper(true);
  }
}

void handleMenu(){
  // Seitenauswahl
  // auswählen
  if (input.button_encoder && !wasMenuButton) {
    d.toggle();
  }
  wasMenuButton = input.button_encoder;

  // drehen
  rotaryEncoder.tick(); // erkenne Reglerdrehungen
  if (rotaryEncoder.getPosition() != rotaryPositionLast) {
    d.change(rotaryEncoder.getPosition() - rotaryPositionLast);
  }
  rotaryPositionLast = rotaryEncoder.getPosition();

  if (input.button_animation && !wasLedButton) {
    isSetupAnimantion = false;
    if (led.isAnimation()) led.cancel(); // beende die Animation
    else led.start();                   // starte die Animation
  }
  else if (input.button_animation && wasLedButton && led.isAnimation() && led.lastAnimation() > 1000) led.hymne();
  wasLedButton = input.button_animation;
  if (isSetupAnimantion && millis() > 3000) {
    isSetupAnimantion = false;
    led.cancel();
  }
}

void kick() {
  if (millis() - kickTimer > 333 && input.switch_kick) {
    digitalWrite(SCHUSS, 1);
    kickTimer = millis();
  }
}

void readCompass() {
  // kompasswert [-180 bis 180]
  bno055_read_euler_hrp(&myEulerData);
  heading = (((myEulerData.h)/16 - startHeading + 720) % 360) - 180;
  debugln(myEulerData.r);
  if(abs(myEulerData.r) < 100)
    flatTimer = millis();
}

void buzzerTone(int duration) {
  if (!silent) {
    analogWrite(BUZZER, 127);
    buzzerStopTimer = max(buzzerStopTimer, millis() + duration);
  }
}


// Roboter mittels PID-Regler zum Tor ausrichten
int ausrichten(int orientation) {
  pidSetpoint = shift(orientation, -179, 180);
  // Misst die Kompassabweichung vom Tor [-180 bis 179]
  if (m.getMotEn()) {
    pidIn = (double) heading;

    double gap = abs(pidSetpoint - pidIn); //distance away from setpoint
    myPID.Compute();

    return -pidOut; // [-255 bis 255]
  }
}

/*****************************************************
  Pixy auslesen: sucht groesten Block in der Farbe des Balls

  SPI-Protokoll:

  INPUT getBlocks():
  Bytes    16-bit words   Description
  ----------------------------------------------------------------
  0, 1     0              sync (0xaa55)
  2, 3     1              checksum (sum of all 16-bit words 2-6)
  4, 5     2              signature number
  6, 7     3              x center of object
  8, 9     4              y center of object
  10, 11   5              width of object
  12, 13   6              height of object

  OUTPUT setServos(servo 0, servo 1):
  Bytes    16-bit words   Description
  ----------------------------------------------------------------
  0, 1     0             sync (0xff00)
  2, 3     1             servo 0 (pan) position, between 0 and 1000
  4, 5     2             servo 1 (tilt) position, between 0 and 1000

  OUTPUT setBrightness(brightness)
  Bytes    16-bit words   Description
  ----------------------------------------------------------------
  0, 1     0             sync (0xfe00)
  2        1             brightness

  OUTPUT setLed(red, green, blue):
  Bytes    16-bit words   Description
  ----------------------------------------------------------------
  0, 1     0              sync (0xfd00)
  2, 3     1              red, green
  4        2              blue
*****************************************************/
void readPixy() {
  if (silent) pixy.setLED(0, 0, 0); // schalte die Front-LED aus
  int ballAreaMax = 0;  // Ballgröße, 0: blind, >0: Flächeninhalt
  int goalAreaMax = 0;  // Torgröße,  0: blind, >0: Flächeninhalt
  int eastHeightMax = 0;  // Farbmarkierungsgröße,  0: blind, >0: Flächeninhalt
  int westHeightMax = 0;  // Farbmarkierungsgröße,  0: blind, >0: Flächeninhalt

  blockCount = pixy.getBlocks();
  blockCountBall = 0;
  blockCountGoal = 0;
  blockCountEast = 0;
  blockCountWest = 0;
  // Liest alle Blöcke aus und zählt diese
  // Sendet "cs error" über USB bei Fehler in Prüfsumme eines empfangenen Objekts

  for (byte i = 0; i < blockCount; i++) { // geht alle erkannten Bloecke durch
    int height = pixy.blocks[i].height;
    int width = pixy.blocks[i].width;
    int x = pixy.blocks[i].x - X_CENTER;
    int signature = pixy.blocks[i].signature;
    int angle = pixy.blocks[i].angle;
    int area = height * width;
    switch (signature) { // Was sehe ich?
      case SIGNATURE_BALL:
        blockCountBall++;
        if (area > ballAreaMax) {
          ballAreaMax = area;
          ball = x;           // merke Ballwinkel
          ballWidth = width;  // merke Ballbreite
          ballArea = area;    // merke Ballgröße
          seeBallTimer = millis();
          if (ballWidth > BALL_WIDTH_TRIGGER) closeBallTimer = millis();
        }
        break;
      case SIGNATURE_GOAL:
        blockCountGoal++;
        if (area > goalAreaMax) {
          goalAreaMax = area;
          goal = x;           // merke Torwinkel
          goalWidth = width;  // merke Torbreite
          goalArea = area;    // merke Torgröße
          seeGoalTimer = millis();
        }
        break;
      case SIGNATURE_CC:
        if (angle < 0) {
          blockCountEast++;
          if (height > eastHeightMax) {
            eastHeightMax = height;
            east = x;
            eastHeight = height;
            seeEastTimer = millis();
          }
        } else {
          blockCountWest++;
          if (height > westHeightMax) {
            westHeightMax = height;
            west = x;
            westHeight = height;
            seeWestTimer = millis();
          }
        }
        break;
    }
    pixyResponseTimer = millis();
  }

  pixyTimer = millis(); // merke Zeitpunkt
}

void rating() {
  scoreBallWidth = seeBall * map(constrain(ballWidth, 0, 130), 0, 130, 0, WEIGHTING_BALL_WIDTH);
  scoreBall = seeBall * map(constrain(abs(ball), 0, X_CENTER), 0, X_CENTER, WEIGHTING_REARWARD, 0);
  scoreRearward = (us.back() > 0) * map(constrain(us.back(), 0, 70), 0, 140, 0, WEIGHTING_REARWARD);
  scoreGoal = map(seeGoal, 0, 1, 0, WEIGHTING_SEE_GOAL);

  if (!seeBall) score = 0;
  else if (p.getState() == 7) score = 255;
  else score = scoreBallWidth + scoreBall + scoreRearward + scoreGoal;
}

String boolToSign(bool b) {
  if (b)
    return "YES ";
  return "NO  ";
}

/*****************************************************
  sende Text zum PC
*****************************************************/
void debug(String str) {
  if (DEBUG && !silent) {
    if (!hasDebugHead) {
      hasDebugHead = true;
      debug(millis());
      if (p.isRusher()) debug("r");
      else debug("k");
      if (seeBall) {
        if (ball < 0) debug(String("    ").substring(0, 4 - String(ball).length()) + String(ball));
        else debug(String("   ").substring(0, 3 - String(ball).length()) + "+" + String(ball));
      } else debug("####");
      if (seeGoal) {
        if (goal < 0) debug(String("    ").substring(0, 4 - String(goal).length()) + String(goal));
        else debug(String("   ").substring(0, 3 - String(goal).length()) + "+" + String(goal));
      } else debug("####");
      debug(driveState + String("          ").substring(0, 10 - driveState.length()));
    }
    DEBUG_SERIAL.print(str + " ");
  }
}
void debug(long num) {
  debug(String(num));
}
void debug() {
  debug("");
}

/*****************************************************
  sende Text zum PC
*****************************************************/
void debugln(String str) {
  debug(str + "\n");
}
void debugln(long num) {
  debugln(String(num));
}
void debugln() {
  debugln("");
}
