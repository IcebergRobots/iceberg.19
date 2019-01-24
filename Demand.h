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

    Timer cooldown;

  private:
    bool demand = false;
    unsigned long lockedPeriod = 0;

};

#endif