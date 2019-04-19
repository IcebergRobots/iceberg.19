#ifndef Motor_h
#define Motor_h

#include "IO.h"
#include "Container.h"

class Motor : public Container
{
  public:
    Motor();
    void setPins(OwnPin *_current, OwnPin *_forward, OwnPin *_backward, OwnPin *_speed);
    void temp(int power);
    void set(int power);
    void set();
    int get();
    void brake(bool active);
    int amperage();
    
    OwnPin *current, *forward, *backward, *speed;
  private:
};

#endif