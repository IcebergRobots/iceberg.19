#include "Chassis.h"

// array auslesen ist schneller als berechnen
const int sinus[360] = {0, 175, 349, 523, 698, 872, 1045, 1219, 1392, 1564, 1736, 1908, 2079, 2250, 2419, 2588, 2756, 2924, 3090, 3256, 3420, 3584, 3746, 3907, 4067, 4226, 4384, 4540, 4695, 4848, 5000, 5150, 5299, 5446, 5592, 5736, 5878, 6018, 6157, 6293, 6428, 6561, 6691, 6820, 6947, 7071, 7193, 7314, 7431, 7547, 7660, 7771, 7880, 7986, 8090, 8192, 8290, 8387, 8480, 8572, 8660, 8746, 8829, 8910, 8988, 9063, 9135, 9205, 9272, 9336, 9397, 9455, 9511, 9563, 9613, 9659, 9703, 9744, 9781, 9816, 9848, 9877, 9903, 9925, 9945, 9962, 9976, 9986, 9994, 9998, 10000, 9998, 9994, 9986, 9976, 9962, 9945, 9925, 9903, 9877, 9848, 9816, 9781, 9744, 9703, 9659, 9613, 9563, 9511, 9455, 9397, 9336, 9272, 9205, 9135, 9063, 8988, 8910, 8829, 8746, 8660, 8572, 8480, 8387, 8290, 8192, 8090, 7986, 7880, 7771, 7660, 7547, 7431, 7314, 7193, 7071, 6947, 6820, 6691, 6561, 6428, 6293, 6157, 6018, 5878, 5736, 5592, 5446, 5299, 5150, 5000, 4848, 4695, 4540, 4384, 4226, 4067, 3907, 3746, 3584, 3420, 3256, 3090, 2924, 2756, 2588, 2419, 2250, 2079, 1908, 1736, 1564, 1392, 1219, 1045, 872, 698, 523, 349, 175, 0, -175, -349, -523, -698, -872, -1045, -1219, -1392, -1564, -1736, -1908, -2079, -2250, -2419, -2588, -2756, -2924, -3090, -3256, -3420, -3584, -3746, -3907, -4067, -4226, -4384, -4540, -4695, -4848, -5000, -5150, -5299, -5446, -5592, -5736, -5878, -6018, -6157, -6293, -6428, -6561, -6691, -6820, -6947, -7071, -7193, -7314, -7431, -7547, -7660, -7771, -7880, -7986, -8090, -8192, -8290, -8387, -8480, -8572, -8660, -8746, -8829, -8910, -8988, -9063, -9135, -9205, -9272, -9336, -9397, -9455, -9511, -9563, -9613, -9659, -9703, -9744, -9781, -9816, -9848, -9877, -9903, -9925, -9945, -9962, -9976, -9986, -9994, -9998, -10000, -9998, -9994, -9986, -9976, -9962, -9945, -9925, -9903, -9877, -9848, -9816, -9781, -9744, -9703, -9659, -9613, -9563, -9511, -9455, -9397, -9336, -9272, -9205, -9135, -9063, -8988, -8910, -8829, -8746, -8660, -8572, -8480, -8387, -8290, -8192, -8090, -7986, -7880, -7771, -7660, -7547, -7431, -7314, -7193, -7071, -6947, -6820, -6691, -6561, -6428, -6293, -6157, -6018, -5878, -5736, -5592, -5446, -5299, -5150, -5000, -4848, -4695, -4540, -4384, -4226, -4067, -3907, -3746, -3584, -3420, -3256, -3090, -2924, -2756, -2588, -2419, -2250, -2079, -1908, -1736, -1564, -1392, -1219, -1045, -872, -698, -523, -349, -175};

/*****************************************************
  setze Achsenwinkel
  @param angle: Achsenwinkel
*****************************************************/
Chassis::Chassis(byte _angle) {
  angle = _angle;
  motEn = false;
}

/*****************************************************
  setze Motor-Ansteuerungspins
  @param id: Motor-ID
  @param _fwd: Pin für Vorwärtsdrehung
  @param _bwd: Pin für Rückwärtsdrehung
  @param _pwm: Pin für Geschwindigkeit
*****************************************************/
void Chassis::setPins(byte id, byte _fwd, byte _bwd, byte _pwm, int _curSens) {
  if (id < 0 || id > 3) { // ungueltige Eingabe
    return;
  }

  fwd[id] = _fwd;         // speichere Pins
  bwd[id] = _bwd;
  pwm[id] = _pwm;

  curSens[id] = _curSens;

  pinMode(_fwd, OUTPUT);   // definiere Pins als Output
  pinMode(_bwd, OUTPUT);
  pinMode(_pwm, OUTPUT);
}

/*****************************************************
  setze den Winkel zwischen zwei Motoren einer Seite (Achsenwinkel)
  @param angle: Achsenwinkel
*****************************************************/
void Chassis::setAngle(byte angle) {
  angle = _angle % 180;
}

/*****************************************************
  setze Ausgangssignale fuer einen Motor
  @param id [0 bis 3]: Motor-ID
  @param power [-255 bis 255]: Gescwindigkeit

  IDs:
     .--.
  0 /    \ 3
  1 \    / 2
     '--'
*****************************************************/
void Chassis::steerMotor(byte id, int power) {
  if (motEn) {
    if (id < 0 || id > 3) {     //Eingabeueberpruefung
      return;
    }

    power = min(255, power);    //Eingabekorrektur
    power = max(-255, power);

    digitalWrite(fwd[id], power > 0);  //drehe Motor vorwarts
    digitalWrite(bwd[id], power <= 0); //drehe Motor rueckwaerts
    analogWrite(pwm[id], abs(power));  //drehe Motor mit Geschwindigkeit
  }
}

/*****************************************************
  fahre mit Geschwindigkeit, Zielwinkel und Eigenrotation
  @param (optional) angle [180 bis 180]: Zielwinkel
  @param (optional) power [-255 bis 255]: Geschwindigkeit
  @param (optional) rotation [-255 bis 255]: Eigenrotation -> Korrekturdrehung, um wieder zum Gegnertor ausgerichtet zu sein

  Winkel:0
      .--.
  90 /    \ -90
     \    /
      '--'
*****************************************************/
void Chassis::drive(int angle, int power, int rotation) {
  calculate(angle, power, rotation);
  drive();
}
void Chassis::drive(int angle, int power) {
  calculate(angle, power);
  drive();
}
void Chassis::drive() {
  drive(values);
}

/*****************************************************
  steuere die Motoren an, um zu fahren
  @param _values: Zwischenspeicher
  - nutze Berechnungen des Zwischenspeichers
*****************************************************/
void Chassis::drive(int _values[]) {
  for (int i = 0; i < 4; i++) {
    steerMotor(i, _values[i]);
  }
}


/*****************************************************
  berechne Zwischenspeicher für Motoransteuerung
  @param angle [180 bis 180]: Zielwinkel
  @param power [-255 bis 255]: Geschwindigkeit
  @param (optional) rotation [-255 bis 255]: Eigenrotation -> Korrekturdrehung, um wieder zum Gegnertor ausgerichtet zu sein
*****************************************************/
void Chassis::calculate(int angle, int power, int rotation) {
  driveDirection = angle;   // setze die Displaywerte
  drivePower = power;       // setze die Displaywerte
  driveRotation = rotation; // setze die Displaywerte

  if (power < 0) {      //bei negativen Geschwindigkeiten,
    power = -power;     //positive Geschwindigkeit
    angle += 180;       //bei 180° Drehung verwenden
  }

  while (angle < 0) {   //Eingabekorrektur
    angle += 360;       //
  }                     //
  angle %= 360;         //

  if (power + abs(rotation) > 255) {        //Wenn die Gesamtgeschwindigkeit zu groß ist,
    power -= (power + abs(rotation)) - 255; //wird die Geschwindigkeit ausreichend reduziert
  }

  //                                                      IDs:  .--.
  int sinA02 = sinus[(((angle / 2) - angle) + 360) % 360]; //berechne Zwischenwert für Achse der Motoren 1 und 3      3 /    \ 0
  int sinA13 = sinus[(((angle / 2) + angle) + 360) % 360]; //berechne Zwischenwert für Achse der Motoren 2 und 4      2 \    / 1
  //                                                            '--'
  int axis02 = power * (double)sinA02 / 10000; //berechne Motorstärken für Achse 1&3
  int axis13 = power * (double)sinA13 / 10000; //berechne Motorstärken für Achse 2&4


  values[0] = axis02 - rotation;       //erstelle Zwischenspeicher für alle Motorstärken
  values[1] = axis13 - rotation;
  values[2] = axis02 + rotation;
  values[3] = axis13 + rotation;

  int totalCurr = 0;
  int totalPwr = 0;

  for (int i = 0; i < 4; i++) {
    int value = analogRead(curSens[i]) - 512;
    totalCurr += abs(value);
    totalPwr += abs(values[i]);
  }
  if (halfSpeed) {
    totalPwr /= 2;
  }
  if (totalPwr != 0) {
    curr = (totalCurr / (float)totalPwr) * 255;
  }

  halfSpeed = !onLine && (power > 30 && curr < 15) || halfSpeed && (power > 15 && curr < 50);

  if (halfSpeed) {
    for (int i = 0; i < 4; i++) {
      values[i] /= 2;
    }
    if (motEn)tone(BUZZER, 700);
  } else {
    noTone(BUZZER);
  }
}
void Chassis::calculate(int angle, int power) {
  calculate(angle, power, 0);
}



/*****************************************************
  bremse aktiv oder passiv alle Motoren
  @param activ: aktives Bremsen?
*****************************************************/
void Chassis::brake(bool activ) {
  drivePower = 0;     // setze die Displaywerte
  driveRotation = 0;  // setze die Displaywerte

  for (byte i = 0; i < 4; i++) {
    digitalWrite(fwd[i], activ);
    digitalWrite(bwd[i], activ);
    analogWrite(pwm[i], 255);
  }
}

void Chassis::setMotEn(bool _motEn) {
  if (motEn != _motEn) {
    motEn = _motEn;
    if (_motEn) {
      p.setRusher(true);
      p.setKeeper(true);
    } else {
      brake(true);
    }
  }
}

void Chassis::switchMotEn() {
  setMotEn(!motEn);
}

bool Chassis::getMotEn() {
  return motEn;
}
