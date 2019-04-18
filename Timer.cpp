#include "Timer.h"

/*****************************************************
  create a timer
  @param _surviveTime: leave output active for a delay
*****************************************************/
Timer::Timer(unsigned long _surviveTime, Timer *_requirement) : Value(BOOLEAN)
{
  setElementType(TIMER);
  surviveTime = _surviveTime;
  requirement = _requirement;
}
/*****************************************************
  set survive time
  @param _surviveTime: leave output active for a delay
*****************************************************/
void Timer::setSurviveTime(unsigned long _surviveTime)
{
  surviveTime = _surviveTime;
}
/*****************************************************
  calculate timings to update active flag
  @param require: external condition to be active
*****************************************************/
void Timer::update()
{
  Value::update();
  refresh();
}
void Timer::refresh()
{
  setWithoutEvent(surviveTime > 0 && insidePeroid(surviveTime));
}
/*****************************************************
  trigger time
  - there is a current event, so save its time (now)
  @param reason: description for event
*****************************************************/
void Timer::now()
{
  if (requirement == NULL || requirement->on())
  {
    Value::now();
    refresh();
  }
}

/*****************************************************
  turn the timer off
*****************************************************/
void Timer::abort() {
  Value::abort();
  refresh();
}