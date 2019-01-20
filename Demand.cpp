#include "Demand.h"

/*********************************************************************
- Konstruktor
*********************************************************************/
Demand::Demand() {
}

/*********************************************************************
- lege die Aufruhe-Häufigkeit fest
*********************************************************************/
void Demand::setCooldown(int min, int max) {
    minDelay = min;
    maxDelay = max; 
}
void Demand::setCooldown(int max) {
    maxDelay = max; 
}

/*********************************************************************
- verlange eine Aktualisierung
*********************************************************************/
void Demand::request() {  
    demand = true;
}

bool Demand::onDemand() {
    bool d = demand;
    demand = false;
    return lastRun == 0
     || (d && millis() - lastRun > minDelay)
     || millis() - lastRun > maxDelay;
}