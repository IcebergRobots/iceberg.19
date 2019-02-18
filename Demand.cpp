#include "Demand.h"

/*********************************************************************
 Constructor
*********************************************************************/
Demand::Demand() {}

/*********************************************************************
  requiere an update as soon as possible
*********************************************************************/
void Demand::request() {  
    demand = true;
}

/*********************************************************************
  is there the need to update the target?
*********************************************************************/
bool Demand::onDemand() {
    if (isEnabled() && locked.off()
    && (locked.outsidePeriod(cooldownTime) || demand)) {
        demand = false;
        locked.set();
        return true;
    }
    return false;
}

/*********************************************************************
  set period of time in which updates are disabled
  @param period: period of time
*********************************************************************/
void Demand::setLocked(unsigned long period) {
    locked.setSurviveTime(period);
}
/*********************************************************************
  set period of time in which updates aren't necessary
  @param period: period of time
*********************************************************************/
void Demand::setCooldown(unsigned long period) {
    cooldownTime = period;
}