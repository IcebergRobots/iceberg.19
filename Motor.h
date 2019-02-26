#ifndef Motor_h
#define Motor_h

#include "IO.h"
#include "Container.h"

class Motor : public Container
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
    void setReal(byte speedInput);
    int getReal();
    
    Pin *current, *forward, *backward, *speed;
  private:
    int realSpeed = 0;
};

#endif