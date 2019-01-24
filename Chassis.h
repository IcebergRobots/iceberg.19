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
    
    Pin *current, *forward, *backward, *speed;
  private:
};

class Chassis
{
  public:
    Motor m[4];

    Chassis();

    void setAxisAngle(byte _axisAngle);

    void drive();
    void drive(int angle, int power=255, int rotation=0);
    void brake(bool active=true);

    void execute();


  private:
    byte axisAngle = 0;
    const int sinus[360];
};
extern class Chassis;

#endif
