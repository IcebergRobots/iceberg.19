#include "Chassis.h"

// array auslesen ist schneller als berechnen
const int sinus[360] = {0, 175, 349, 523, 698, 872, 1045, 1219, 1392, 1564, 1736, 1908, 2079, 2250, 2419, 2588, 2756, 2924, 3090, 3256, 3420, 3584, 3746, 3907, 4067, 4226, 4384, 4540, 4695, 4848, 5000, 5150, 5299, 5446, 5592, 5736, 5878, 6018, 6157, 6293, 6428, 6561, 6691, 6820, 6947, 7071, 7193, 7314, 7431, 7547, 7660, 7771, 7880, 7986, 8090, 8192, 8290, 8387, 8480, 8572, 8660, 8746, 8829, 8910, 8988, 9063, 9135, 9205, 9272, 9336, 9397, 9455, 9511, 9563, 9613, 9659, 9703, 9744, 9781, 9816, 9848, 9877, 9903, 9925, 9945, 9962, 9976, 9986, 9994, 9998, 10000, 9998, 9994, 9986, 9976, 9962, 9945, 9925, 9903, 9877, 9848, 9816, 9781, 9744, 9703, 9659, 9613, 9563, 9511, 9455, 9397, 9336, 9272, 9205, 9135, 9063, 8988, 8910, 8829, 8746, 8660, 8572, 8480, 8387, 8290, 8192, 8090, 7986, 7880, 7771, 7660, 7547, 7431, 7314, 7193, 7071, 6947, 6820, 6691, 6561, 6428, 6293, 6157, 6018, 5878, 5736, 5592, 5446, 5299, 5150, 5000, 4848, 4695, 4540, 4384, 4226, 4067, 3907, 3746, 3584, 3420, 3256, 3090, 2924, 2756, 2588, 2419, 2250, 2079, 1908, 1736, 1564, 1392, 1219, 1045, 872, 698, 523, 349, 175, 0, -175, -349, -523, -698, -872, -1045, -1219, -1392, -1564, -1736, -1908, -2079, -2250, -2419, -2588, -2756, -2924, -3090, -3256, -3420, -3584, -3746, -3907, -4067, -4226, -4384, -4540, -4695, -4848, -5000, -5150, -5299, -5446, -5592, -5736, -5878, -6018, -6157, -6293, -6428, -6561, -6691, -6820, -6947, -7071, -7193, -7314, -7431, -7547, -7660, -7771, -7880, -7986, -8090, -8192, -8290, -8387, -8480, -8572, -8660, -8746, -8829, -8910, -8988, -9063, -9135, -9205, -9272, -9336, -9397, -9455, -9511, -9563, -9613, -9659, -9703, -9744, -9781, -9816, -9848, -9877, -9903, -9925, -9945, -9962, -9976, -9986, -9994, -9998, -10000, -9998, -9994, -9986, -9976, -9962, -9945, -9925, -9903, -9877, -9848, -9816, -9781, -9744, -9703, -9659, -9613, -9563, -9511, -9455, -9397, -9336, -9272, -9205, -9135, -9063, -8988, -8910, -8829, -8746, -8660, -8572, -8480, -8387, -8290, -8192, -8090, -7986, -7880, -7771, -7660, -7547, -7431, -7314, -7193, -7071, -6947, -6820, -6691, -6561, -6428, -6293, -6157, -6018, -5878, -5736, -5592, -5446, -5299, -5150, -5000, -4848, -4695, -4540, -4384, -4226, -4067, -3907, -3746, -3584, -3420, -3256, -3090, -2924, -2756, -2588, -2419, -2250, -2079, -1908, -1736, -1564, -1392, -1219, -1045, -872, -698, -523, -349, -175};

/*****************************************************
  setze Achsenwinkel
  @param angle: Achsenwinkel
*****************************************************/
Chassis::Chassis(byte _axisAngle) {
  setAxisAngle(_axisAngle);
  io.driveEnabled.set(true);
  m[0].setPins(&io.m0Current, &io.m0Dir1, &io.m0Dir2, &io.m0Speed);
  m[1].setPins(&io.m1Current, &io.m1Dir1, &io.m1Dir2, &io.m1Speed);
  m[2].setPins(&io.m2Current, &io.m2Dir1, &io.m2Dir2, &io.m2Speed);
  m[3].setPins(&io.m3Current, &io.m3Dir1, &io.m3Dir2, &io.m3Speed);
}

/*****************************************************
  setze den Winkel zwischen zwei Motoren einer Seite (Achsenwinkel)
  @param angle: Achsenwinkel
*****************************************************/
void Chassis::setAxisAngle(byte _axisAngle) {
  axisAngle = circulate(_axisAngle, 0, 180);
}


/*****************************************************
  berechne Zwischenspeicher für Motoransteuerung
  @param angle [-180 bis 180]: Zielwinkel
  @param power [-255 bis 255]: Geschwindigkeit
  @param (optional) rotation [-255 bis 255]: Eigenrotation -> Korrekturdrehung, um wieder zum Gegnertor ausgerichtet zu sein
*****************************************************/
void Chassis::temp(int angle, int power, int rotation) {
  io.driveAngle.set(angle);
  if (power < 0)  io.driveAngle.add(180);       //bei 180° Drehung verwenden
  io.drivePower.set(abs(power));
  io.driveRotation.set(rotation);
  
  io.drivePower.add(min(0, 255 - io.drivePower.get() - abs(io.driveRotation.get()))); // Wenn die Gesamtgeschwindigkeit zu groß ist, wird die Geschwindigkeit ausreichend reduziert

  int sinA02 = sinus[circulate((axisAngle / 2) - io.driveAngle.get(), 0, 359)]; //berechne Zwischenwert für Achse der Motoren 1 und 3 
  int sinA13 = sinus[circulate((axisAngle / 2) + io.driveAngle.get(), 0, 359)]; //berechne Zwischenwert für Achse der Motoren 2 und 4

  int axis02 = io.drivePower.get() * (double)sinA02 / 10000; //berechne Motorstärken für Achse 1&3
  int axis13 = io.drivePower.get() * (double)sinA13 / 10000; //berechne Motorstärken für Achse 2&4

  m[0].temp(-axis02 + io.driveRotation.get());
  m[1].temp(-axis13 + io.driveRotation.get());
  m[2].temp( axis02 + io.driveRotation.get());
  m[3].temp( axis13 + io.driveRotation.get());
}

/*****************************************************
  berechne Zwischenspeicher für Motoransteuerung
  @param angle [-180 bis 180]: Zielwinkel
  @param power [-255 bis 255]: Geschwindigkeit
  @param (optional) rotation [-255 bis 255]: Eigenrotation -> Korrekturdrehung, um wieder zum Gegnertor ausgerichtet zu sein
*****************************************************/
void Chassis::set(int angle, int power, int rotation) {
  temp(angle, power, rotation);
  set();
}

/*****************************************************
  steuere die Motoren an, um zu fahren
  @param _values: Zwischenspeicher
  - nutze Berechnungen des Zwischenspeichers
*****************************************************/
void Chassis::set() {
  if (io.driveEnabled.on()) for (int i = 0; i < 4; i++) m[i].set();
}

/*****************************************************
  bremse aktiv oder passiv alle Motoren
  @param activ: aktives Bremsen?
*****************************************************/
void Chassis::brake(bool active) {
  io.drivePower.set(0);
  io.driveRotation.set(0);

  for (int i = 0; i < 4; i++) m[i].brake(active);
}

Chassis drive;




Motor::Motor() {}

void Motor::setPins(Pin *_current, Pin *_forward, Pin *_backward, Pin *_speed) {
  current = _current;
  forward = _forward;
  backward = _backward;
  speed = _speed;
}

void Motor::temp(int power) {
  forward->temp(power > 0);
  backward->temp(power <= 0);
  speed->temp(abs(power)); 
}

void Motor::set(int power) {
  temp(power);
  set();
}

void Motor::set() {
  forward->set();
  backward->set();
  speed->set(); 
}

int Motor::get() {
  return speed->get();
}

void Motor::brake(bool active) {
  forward->set(active);
  backward->set(active);
  speed->set(255); 
}

int Motor::amperage() {
  return current->get(); 
}