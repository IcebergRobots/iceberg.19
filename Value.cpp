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
Value::Value(byte processing, int _min, int _max) {
  switch (processing) {
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
void Value::setLimits(int _min, int _max) {
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
void Value::setModulation(int _min, int _max) {
  a = max(_min, _max);
  b = min(_min, _max);
  value = circulate(value, b, a);
}

/*****************************************************
  reset change state as the change happend durring the previous loop
*****************************************************/
void Value::update() {
  if      (getState() == FALLING) setState(OFF);
  else if (getState() == RISING)  setState(ON);
  state = getState();
}

/*****************************************************
  there is a current event, so save its time (now)
*****************************************************/
void Value::now(bool mute) {
  if (!mute) sendDebug();
  eventTimer = millis();
}
/*****************************************************
  set a new value process it
  @param _value: new value
  - modulate or limit the value
*****************************************************/
bool Value::muteSet(int _value) {
  int lastValue = value;
  if (value != _value) {
    if (a <= b) value = constrain(_value, a, b); // limit
    else value = circulate(_value, b, a);        // modulate

    // if sign doesn't change, keep falling or rising state and wait for update()
    if (value != lastValue) {
      switch (getState()) {
        case OFF:
        case FALLING:
          if (on())  setState(RISING);
          break;

        case ON:
        case RISING:
          if (off()) setState(FALLING);
          break;

        default:
          break;
      }
      state = -getState();
    }
  }
  return value != lastValue;
}
void Value::set(int _value, byte pin) {
  if (muteSet(_value)) {
    now(true); // trigger the timer because value changed
    if (isDebug(DEBUG_ON_CHANGE)) sendDebug(pin);
  }
}
void Value::set(int _value, String reason, byte pin) {
  if (muteSet(_value)) {
    now(true);
    if (isDebug(DEBUG_ON_CHANGE)
    || (isDebug(DEBUG_ON_REASON) && reason.length() > 0)) {
      sendDebug(reason, pin);
    }
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
void Value::sendDebug(byte pin) {
  if (isDebug()) {
    debug(prepareDebug(pin));
  }
}
void Value::sendDebug(String reason, byte pin) {
  if (isDebug()) {
    String m = prepareDebug(pin);
    if (isDebug(DEBUG_REASON)) m += ":" + reason;
    debug(m);
  }
}

String Value::prepareDebug(byte pin) {
  String m;
  if (isDebug(DEBUG_FOR_PLOTTER)) {
    m = str() + ",";
  } else {
    m = "§";
    if (isDebug(DEBUG_PIN)) { 
      if (isFinite(pin))  m += String(pin);
      else                m += String((int)this);
      m += "|";
    }
    if (isDebug(DEBUG_TIME))  m += String(millis()) + "|";
    if (isDebug(DEBUG_VALUE)) m += str();
  }
  return m;
}

void Value::setElementType(byte type) {
  if (type > elementType) elementType = type;
}

byte Value::getElementType() {
  return elementType;
}

void Value::setState(byte s) {
  if (state < 0) state = -s;
  else state = s;
}

char Value::getState() {
  return abs(state);
}

void Value::abort(){
  if (ever()) eventTimer = 1;
  muteSet(0);
}