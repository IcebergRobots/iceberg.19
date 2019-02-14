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
Value::Value(byte processing, int min, int max) {
  objects.add(*this);
  switch (processing) {
    default:
    case LIMITS:
      setLimits(min, max);
      break;
    case MODULATION:
      setModulation(min, max);
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
void Value::setLimits(int min, int max) {
  a = min(min, max);
  b = max(min, max);
  set(value);
}
/*****************************************************
  configurate modulation
  @param min: lower limit
  @param max: upper limit
  - see header file for visualisation
*****************************************************/
void Value::setModulation(int min, int max) {
  a = max(min, max);
  b = min(min, max);
  set(value);
}

/*****************************************************
  reset change state as the change happend durring the previous loop
*****************************************************/
void Value::update() {
  if      (state == FALLING) state = OFF;
  else if (state == RISING)  state = ON;
}

/*****************************************************
  there is a current event, so save its time (now)
*****************************************************/
void Value::now(bool mute) {
  if (!mute) sendDebug(true);
  eventTimer = millis();
}
/*****************************************************
  set a new value process it
  @param _value: new value
  - modulate or limit the value
*****************************************************/
void Value::set(int _value, String reason, bool mute, byte pin) {
  if (value != _value) {
    if (a <= b) value = constrain(_value, a, b); // limit
    else value = circulate(_value, a, b);        // modulate

    if (value != _value) return; // value didn't change

    if (!mute) {
      now(true); // trigger the timer because value changed
      if (isDebug(DEBUG_ON_CHANGE)                             // event causes message
      || (isDebug(DEBUG_ON_REASON) && reason.length() > 0)) {  // reason causes message
        sendDebug(!mute, reason, pin);
      }
    }

    // if sign doesn't change, keep falling or rising state and wait for update()
    if (state == OFF || state == FALLING) if (on())  state = RISING;  // detect rising (off -> on) change
    else                                  if (off()) state = FALLING; // detect falling (on -> off) change
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
  return value
*****************************************************/
int Value::get() { return value; }
/*****************************************************
  is the value positive?
*****************************************************/
bool Value::on() { return value > 0; }
/*****************************************************
  is value negative or zero?
*****************************************************/
bool Value::off() { return value <= 0; }
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
  convert number to formatted string
  @param minLength: minimun length of the string
  @param maxLength: maximun length of the string
  @param sign: add a plus sign
*****************************************************/
String Value::str(unsigned int minLength, unsigned int maxLength, bool sign) { 
  return format(value, minLength, maxLength, sign); 
}

/*****************************************************
  did the value fall?
*****************************************************/
bool Value::falling() { return state == FALLING; }
/*****************************************************
  did the value fall?
*****************************************************/
bool Value::rising() { return state == RISING; }
/*****************************************************
  did the value fall?
*****************************************************/
bool Value::change() { return falling() || rising(); }

/*****************************************************
  was there ever an event?
*****************************************************/
bool Value::ever() { return eventTimer != 0; }
/*****************************************************
  was there ever an event?
*****************************************************/
bool Value::never() { return !ever(); }
/*****************************************************
  time since last event
*****************************************************/
unsigned long Value::period() {
  if (never()) return -1;
  else return millis() - eventTimer;
}
/*****************************************************
  happened the last event outside this period
*****************************************************/
bool Value::outsidePeriod(unsigned long min) {
  return !insidePeroid(min);
}/*****************************************************
  happened the last event within this period
*****************************************************/
bool Value::insidePeroid(unsigned long max) {
  return max + 1 == 0 || (ever() && period() <= max);
}
/*****************************************************
  time since last event as string
  @param minLength: minimun length of the string
  @param maxLength: maximun length of the string
  @param sign: add a plus sign
*****************************************************/
String Value::periodStr(unsigned int minLength, unsigned int maxLength, bool sign) {
  return format(period(), minLength, maxLength, sign); 
}

/*****************************************************
  configurate a special type of debugging
  @param type: select an aspect
  @param enable: show this aspect be displayed?
*****************************************************/
void Value::showDebug(byte type, bool enable) {
  bitWrite(debugSettings, type, enable);
}
/*****************************************************
  activate debugging
*****************************************************/
void Value::startDebug() { showDebug(DEBUG_ENABLE); }
/*****************************************************
  deactivate debugging
*****************************************************/
void Value::stopDebug() { showDebug(DEBUG_ENABLE, false); }
/*****************************************************
  turn all aspects of debugging off
*****************************************************/
void Value::resetDebug() { debugSettings = B00000000; }

/*****************************************************
  is this type of debugging activated?
*****************************************************/
bool Value::isDebug(byte type) {
  return bitRead(debugSettings, DEBUG_ENABLE) && bitRead(debugSettings, type);
}
/*****************************************************
  create a new debug message
*****************************************************/
void Value::sendDebug(bool timerChange, String reason, byte pin) {
  if (!isDebug()) return;
  String m = "§";
  if (isDebug(DEBUG_PIN)) { 
    if (isFinite(pin)) m += String(pin) + "|";
    else m += "v";
  }
  if (isDebug(DEBUG_TIME)) m += String(millis()) + "|";
  if (isDebug(DEBUG_STATE)) {
    switch (state) {
      case OFF:
        m += "o";
        break;
      case ON:
        m += "i";
        break;
      case FALLING:
        m += "f";
        break;
      case RISING:
        m += "r";
        break;
      default:
        m += "?";
        break;
    }
  }
  if (isDebug(DEBUG_VALUE)) m += str();
  if (isDebug(DEBUG_REASON)) m += reason;
  debug(m);
  
}