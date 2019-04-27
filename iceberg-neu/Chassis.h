#ifndef Chassis_h
#define Chassis_h

#include "Motor.h"

class Chassis
{
  public:
    Motor m[4];

    Chassis();

    void setAxisAngle(byte _axisAngle);

    void drive();
    void drive(int angle, int power=255, int rotation=0);
    void brake();

    void execute(bool force=false);

  private:
    byte axisAngle = 0;
};

#endif
