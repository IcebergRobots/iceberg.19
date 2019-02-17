#ifndef Demand_h
#define Demand_h

#include "Value.h"

class Demand
{
  public:
    Demand();
    void setLocked(unsigned long period);
    void setCooldown(unsigned long period);
    void request();
    bool onDemand();

    Value runTime;

  private:
    bool demand = false;
    unsigned long lockedTime = 0;
    unsigned long cooldownTime = 0;

};

#endif