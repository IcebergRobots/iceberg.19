#include "Pin.h"

/*****************************************************
  configurate an arduino pin
  @param _pin: pin address
  @param _mode: pinmode (OUTPUT, INPUT, INPUT_PULLUP)
  @param _type: type of pin (ANALOG, DIGITAL, PWM, PUI, VIRTUAL)
  - set pinMode
  - configurate limits automatically
*****************************************************/
Pin::Pin(byte _pin, byte _mode, byte _type) : Value() {
  pin = _pin;
  mode = _mode;
  type = _type;
  switch (type) {
    case ANALOG:
      digital = false;
      pinMode(pin, mode);
      break;

    case PWM:
      digital = (mode != OUTPUT);
      pinMode(pin, mode);
      break;

    case DIGITAL:
      pinMode(pin, mode);
    case PUI:
    case VIRTUAL:
    default:
      digital = true;
      break;
  }
  if(type != VIRTUAL) {
    if(digital) setLimits(0, 1);
    else setLimits(0, 255);
  }
}

/*****************************************************
  output a signal on the arduino pin
  @param _value: output signal
*****************************************************/
void Pin::set(int _value) {
  temp(_value);
  set();
}
void Pin::set(int _value, String reason) {
  temp(_value, reason);
  set();
}

/*****************************************************
  output the temporary saved signal on the arduino pin
*****************************************************/
void Pin::set() {
  if (mode == OUTPUT) {
    switch (type) {
      case ANALOG:
      case DIGITAL:
      case PWM:
        if(digital) digitalWrite(pin, get());
        else analogWrite(pin, get());
      break;

      case PUI:
        pui.set(pin, get());
      break;

      case VIRTUAL:
      default:
      break;
    }
  }
}

/*****************************************************
  save value temporary without changing the arduino pin output
  @param _value: output signal
  - wait for set() to execute changes
*****************************************************/
void Pin::temp(int _value) {
  Value::set(_value, getPin());
}
void Pin::temp(int _value, String reason) {
  Value::set(_value, reason, getPin());
}

/*****************************************************
  read the arduino pin
  - will ignore output pins
*****************************************************/
void Pin::update() {
  Value::update();
  if(mode != OUTPUT) {
    switch (type)
    {
      case VIRTUAL:
        return;
      case ANALOG:
      case DIGITAL:
      case PWM:
        if (digital) set(digitalRead(pin));
        else set(analogRead(pin));
      break;
      case PUI:
        set(pui.get(pin));
      break;
    }
    if(mode == INPUT_PULLUP && type != VIRTUAL) set(!get());
  }
}

/*****************************************************
  return pin address
*****************************************************/
byte Pin::getPin() {
	return pin;
}