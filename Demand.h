#ifndef Demand_h
#define Demand_h

#include "Timer.h"

class Demand
{
  public:
    Demand();
    void setLocked(unsigned long period);
    void setCooldown(unsigned long period);
    void request();
    bool onDemand();

    virtual bool isEnabled() = 0;

    Timer locked;

  private:
    bool demand = false;
    unsigned long cooldownTime = 0;

};

#endif