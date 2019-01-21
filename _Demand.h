#ifndef Demand_h
#define Demand_h

#include "core.h"

class Demand
{
  public:
    Demand();
    void request();
    bool onDemand();
    void setCooldown(int min , int max);
    void setCooldown(int max);

  private:
    bool demand = false;
    unsigned long lastRun = 0;
    unsigned long minDelay = 0;
    unsigned long maxDelay = 0;
};

#endif