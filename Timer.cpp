#include "Timer.h"

/*****************************************************
  create a timer
  @param _surviveTime: leave output active for a delay
*****************************************************/
Timer::Timer(unsigned long _surviveTime, Timer *_requirement) : Value(MODULATION, false, true) {
  surviveTime = _surviveTime;
  requirement = _requirement;
}
/*****************************************************
  set survive time
  @param _surviveTime: leave output active for a delay
*****************************************************/
void Timer::setSurviveTime(unsigned long _surviveTime) {
  surviveTime = _surviveTime;
}
/*****************************************************
  calculate timings to update active flag
  @param require: external condition to be active
*****************************************************/
void Timer::update() {
  Value::update();
  if(ever() && surviveTime > 0) Value::set(insidePeroid(surviveTime), "", false);
}
/*****************************************************
  trigger time
  - set timer to current time
*****************************************************/
void Timer::set(bool active) {
  if (active && (requirement == NULL || requirement->on())) now();
  update();
}