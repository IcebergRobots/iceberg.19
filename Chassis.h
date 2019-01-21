#ifndef Chassis_h
#define Chassis_h

#include "Config.h"

class Chassis
{
  public:
    Chassis(byte _angle=70);

    void setPins(byte id, byte _fwd, byte _bwd, byte _pwm, int _curSens);
    void setAngle(byte _angle);

    void steerMotor(byte id, int power);

    void drive();
    void drive(int _values[]);
    void drive(int _angle, int power);
    void drive(int _angle, int power, int rotation);

    void calculate(int _angle, int power);
    void calculate(int _angle, int power, int rotation);

    void brake(bool activ);

    void setMotEn(bool _motEn);
    bool getMotEn();
    void switchMotEn();

  private:
    byte fwd[4];    // digitaler PIN fuer Vorwaertsrotation
    byte bwd[4];    // digitaler PIN fuer Rueckwaertsrotation
    byte pwm[4];    // analoger PIN fuer Geschwindigkeit

    byte curSens[4];

    int values[4];  // Zwischenspeicher für Outputsignale

    byte angle;
    bool motEn;    // gibt an, ob die Motoren an sind
    bool halfSpeed = false;

    int curr;
};

#endif
