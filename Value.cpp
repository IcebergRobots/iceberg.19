#include "Value.h"

/*****************************************************
  create a new value
  @param processing: processing mode (LIMITS, MODULATION)
  @param min:
    - in case of modulation: upper limit
    - in case of limits: lower limit
  @param max:
    - in case of modulation: lower limit
    - in case of limits: upper limit
*****************************************************/
Value::Value(byte processing, int _min, int _max)
{
  switch (processing)
  {
  default:
  case LIMITS:
    setLimits(_min, _max);
    break;
  case MODULATION:
    setModulation(_min, _max);
    break;
  case BOOLEAN:
    setLimits(false, true);
    break;
  }
}
/*****************************************************
  configurate limits
  @param min: lower limit
  @param max: upper limit
  - see header file for visualisation
*****************************************************/
void Value::setLimits(int _min, int _max)
{
  a = min(_min, _max);
  b = max(_min, _max);
  value = constrain(value, a, b);
}
/*****************************************************
  configurate modulation
  @param min: lower limit
  @param max: upper limit
  - see header file for visualisation
*****************************************************/
void Value::setModulation(int _min, int _max)
{
  a = max(_min, _max);
  b = min(_min, _max);
  value = circulate(value, b, a);
}

/*****************************************************
  reset change state as the change happend durring the previous loop
*****************************************************/
void Value::update()
{
  if (getState() == FALLING)
    setState(OFF);
  else if (getState() == RISING)
    setState(ON);
  state = getState();
}

/*****************************************************
  there is a current event, so save its time (now)
*****************************************************/
void Value::now()
{
  eventTimer = millis();
}
/*****************************************************
  set a new value process it
  @param _value: new value
  - modulate or limit the value
*****************************************************/
bool Value::setWithoutEvent(int _value)
{
  if (value != _value)
  {
    int lastValue = value;
    if (a <= b)
      value = constrain(_value, a, b); // limit
    else
      value = circulate(_value, b, a); // modulate

    // if sign doesn't change, keep falling or rising state and wait for update()
    if (value != lastValue)
    {
      switch (getState())
      {
      case OFF:
      case FALLING:
        if (on())
          setState(RISING);
        break;

      case ON:
      case RISING:
        if (off())
          setState(FALLING);
        break;

      default:
        break;
      }
      state = -getState();
      return true;  // value did change
    }
  }
  return false; // value did not change
}
void Value::set(int _value, byte pin)
{
  if (setWithoutEvent(_value))
  {
    now(); // trigger the timer because value changed
  }
}

/*****************************************************
  change the value
  @param _summand: summand
*****************************************************/
void Value::add(int _summand) { set(value + _summand); }
/*****************************************************
  scale the value
  @param _factor: factor
*****************************************************/
void Value::mul(float _factor) { set(value * _factor); }
/*****************************************************
  toggle between off and on
*****************************************************/
void Value::toggle() {
  if (on()) setLow();
  else setHigh();
}
/*****************************************************
  set to the maximum value
*****************************************************/
void Value::setHigh() {
  set(max(a, b));
}
/*****************************************************
  set to the minimun value
*****************************************************/
void Value::setLow() {
  set(0);
}


/*****************************************************
  return value
*****************************************************/
int Value::get() { return value; }
/*****************************************************
  is the value positive?
*****************************************************/
bool Value::on() { return value != 0; }
/*****************************************************
  is value negative or zero?
*****************************************************/
bool Value::off() { return value == 0; }
/*****************************************************
  points the angle right?
  @param tolerance: tolerance angle for center direction
  - value=true is right
*****************************************************/
bool Value::right(int tolerance) { return value > tolerance; }
/*****************************************************
  points the angle left?
  @param tolerance: tolerance angle for center direction
  - value=false is left
*****************************************************/
bool Value::left(int tolerance) { return value <= -tolerance; }
/*****************************************************
  points the angle straight
  @param tolerance: tolerance angle for center direction
*****************************************************/
bool Value::center(int tolerance) { return abs(value) <= tolerance; }
/*****************************************************
  is the comparison true?
  @param comparison: value to compare
*****************************************************/
bool Value::is(int comparison) { return value == comparison; }
/*****************************************************
  is the comparison false?  
  @param comparison: value to compare
*****************************************************/
bool Value::no(int comparison) { return value != comparison; }

/*****************************************************
  did the value fall?
*****************************************************/
bool Value::falling() { return getState() == FALLING; }
/*****************************************************
  did the value fall?
*****************************************************/
bool Value::rising() { return getState() == RISING; }
/*****************************************************
  did the value fall?
*****************************************************/
bool Value::change() { return state < 0; }

/*****************************************************
  was there ever an event?
*****************************************************/
bool Value::ever() { return eventTimer != 0; }
/*****************************************************
  was there ever an event?
*****************************************************/
bool Value::never() { return eventTimer == 0; }
/*****************************************************
  ist der Zeitstempel gültig?
  - gibt der Timer den Zeitpunkt des letzten Events an?
*****************************************************/
bool Value::timerValid() {
  return eventTimer > 1;
}
/*****************************************************
  time since last event
*****************************************************/
unsigned long Value::period()
{
  if (timerValid())
    return millis() - eventTimer;
  else
    return -1;
}
/*****************************************************
  happened the last event outside this period
*****************************************************/
bool Value::outsidePeriod(unsigned long min)
{
  return !insidePeroid(min);
} /*****************************************************
  happened the last event within this period
*****************************************************/
bool Value::insidePeroid(unsigned long max)
{
  return ever() && period() <= max;
}



void Value::setElementType(byte type)
{
  if (type > elementType)
    elementType = type;
}

byte Value::getElementType()
{
  return elementType;
}

void Value::setState(byte s)
{
  if (state < 0)
    state = -s;
  else
    state = s;
}

char Value::getState()
{
  return abs(state);
}

/*****************************************************
  reset the event timer
*****************************************************/
void Value::abort()
{
  if (ever())
    eventTimer = 1;
}