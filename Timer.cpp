#include "Timer.h"

/*****************************************************
  create a timer
  @param _surviveTime: leave output active for a delay
*****************************************************/
Timer::Timer(unsigned long _surviveTime, Timer *_requirement) : Value(MODULATION, false, true) {
  setElementType(TIMER);
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
  if(surviveTime > 0) Value::set(insidePeroid(surviveTime), "", true);
}
/*****************************************************
  trigger time
  - there is a current event, so save its time (now)
  @param active: new value
*****************************************************/
void Timer::set(bool active) {
  if (active && (requirement == NULL || requirement->on())) now();
  update();
}
/*****************************************************
  time since last event as string
  @param minLength: minimun length of the string
  @param maxLength: maximun length of the string
  @param sign: add a plus sign
*****************************************************/
String Timer::str(unsigned int minLength, unsigned int maxLength, bool sign) {
  return format(period(), minLength, maxLength, sign); 
}
