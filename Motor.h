#ifndef Motor_h
#define Motor_h

#include "IO.h"

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
    
    Pin *current, *forward, *backward, *speed;
  private:
};

#endif