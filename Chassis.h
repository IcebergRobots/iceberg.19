#ifndef Chassis_h
#define Chassis_h

#include "core.h"

class Motor
{
  public:
    Motor();
    void setPins(Pin *_current, Pin *_forward, Pin *_backward, Pin *_speed);
    void temp(int power);
    void set(int power);
    void set();
    int get();
    void brake(bool active);
    int amperage();
  private:
    Pin *current, *forward, *backward, *speed;
};

class Chassis
{
  public:
    Motor m[4];

    Chassis(byte _axisAngle=70);

    void setAxisAngle(byte _axisAngle);

    void temp(int angle, int power=255, int rotation=0);
    void set(int angle, int power=255, int rotation=0);
    void set();


    void brake(bool active);

  private:
    byte axisAngle = 0;
};
extern Chassis drive;

#endif
