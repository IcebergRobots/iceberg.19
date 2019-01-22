#include "IO.h"

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
void Value::now() {
  eventTimer = millis();
}
/*****************************************************
  set a new value process it
  @param _value: new value
  - modulate or limit the value
*****************************************************/
void Value::set(int _value, bool trigger) {
  if (value != _value) {
    if (a <= b) value = constrain(_value, a, b); // limit
    else value = circulate(_value, a, b);       // modulate

    if (value != _value) return; // value didn't change

    if (trigger) now(); // trigger the timer because value changed

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
  time since last event
*****************************************************/
unsigned long Value::since() {
  if (!ever()) return -1;
  else return millis() - eventTimer;
}
String Value::sinceStr(unsigned int minLength, unsigned int maxLength, bool sign) {
  return format(since(), minLength, maxLength, sign); 
}





/*****************************************************
  create a timer
  @param _surviveTime: leave output active for a delay
*****************************************************/
  Timer::Timer(long _surviveTime, Timer *_requirement) : Value(MODULATION, false, true) {
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
  if(ever()) Value::set(since() <= surviveTime, false);
}
/*****************************************************
  trigger time
  - set timer to current time
*****************************************************/
void Timer::set(bool active) {
  if (active && (requirement == NULL || requirement->on())) now();
  update();
}





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
  Value::set(_value);
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




/*****************************************************
  configurate an arduino pin as a key
  @param _pin: pin address
  @param _type: type of pin (ANALOG, DIGITAL, PWM, PUI, VIRTUAL)
  @param _preStroke: delay befor the first click
  @param _postStroke: delay after the first click
  @param _postFurther: delay after second or later click
  - see header file for visualisation
*****************************************************/
Key::Key(byte _pin, byte _type, unsigned long _preStroke, unsigned long _postStroke, unsigned long _postFurther)
 : Pin(_pin, INPUT_PULLUP, _type) {
  preStroke = _preStroke;
  postStroke = _postStroke;
  postFurther = _postFurther;
}

/*****************************************************
  is there a first click?
*****************************************************/
bool Key::stroke() { return state == STROKE; }
/*****************************************************
  is there a second or later click?
*****************************************************/
bool Key::further() { return state == FURTHER; }
/*****************************************************
  is there any click?
*****************************************************/
bool Key::click() { return stroke() || further(); }

/*****************************************************
  read the arduino pins and process it to detect clicks
*****************************************************/
void Key::update() {
  Pin::update();
	if(off()) state = OFF; // Knopf ist losgelassen
	else { // Knopf wird gedrückt
    switch (state) {
      default:
      case OFF: // so far no click was detected
        if (since() >= preStroke) {
          state = STROKE; // detect the first click
          now(); // create an event and save click time
        }
        break;
      case ON:
      case STROKE:
        if (since() >= postStroke) {
          state = FURTHER;  // detect a further click
          now(); // create an event and save click time
        } else state = ON;
        break;
      case FURTHER:
        if (since() >= preStroke) {
          state = FURTHER;  // detect a further click
          now(); // create an event and save click time
        } else state = ON;
        break;
    }
	}
}





/*****************************************************
  combine keys to a shortcut
  @param _keys: two dimensional array of key pointers:
    - create array: Key *array = {&key1, &key2, ...};
    - insert array
  @param _keysLength: 
    - length of the keys array
    - number of keys in the shortcut
  @param _muteKeys: if the shortcut is active, should the individual keys detect clicks?
  @param _preStroke: delay befor the first shortcut click
  @param _postStroke: delay after the first shortcut click
  @param _postFurther: delay after second or later shortcut click
*****************************************************/
Shortcut::Shortcut(Key **_keys, byte _keysLength, bool _muteKeys, unsigned long _preStroke, unsigned long _postStroke, unsigned long _postFurther)
 : Key(0, VIRTUAL, _preStroke, _postStroke, _postFurther) {
  keys = _keys;
  keysLength = _keysLength;
  muteKeys = _muteKeys;
}

/*****************************************************
  scan all individual keys and process to detect clicks
*****************************************************/
void Shortcut::update() {
  set(true); // activate virtual key
  for(int i = 0; i < keysLength; i++) {
    if (keys[i]->off()) { // this key inactive
      set(false); // shortcut is inactive
      break; // skip other keys
    }
  }
  if(on() && muteKeys) {
    for(int i = 0; i < keysLength; i++) {
      keys[i]->set(false); // deactivate key to prevent their functions 
      keys[i]->update();
    }
  }
  Key::update(); // is this shortcut active (stroke, further, click)?
}



/*****************************************************
  create a physical user interface
*****************************************************/
Pui::Pui() {}

/*****************************************************
  initialise communication
*****************************************************/
void Pui::init() {
  beginSegment("pui");
  I2c.write(ADDRESS, A_PINMODE, 0x00); // set OUTPUT
  I2c.write(ADDRESS, B_PINMODE, 0xFF);  // set INPUT
  I2c.write(ADDRESS, B_VALUE, 0xFF);    // set INPUT_PULLUP
  endSegment();
}

/*****************************************************
  output a signal on the pui pin
  @param _value: output signal
*****************************************************/
void Pui::set(byte pin, bool value) {
  if(pin < 8) {
    bitWrite(a, pin, value);
    I2c.write(ADDRESS, A_VALUE, a);
  }
}

/*****************************************************
  return the temporary saved pui pin signal
*****************************************************/
bool Pui::get(byte pin) {
  if(pin < 8) return bitRead(a, pin);
  else return bitRead(b, pin-8);
}

/*****************************************************
  read all pui pins
*****************************************************/
void Pui::update() {
  I2c.read(ADDRESS, A_VALUE, 1);
  b = I2c.receive();
}

Pui pui = Pui();


/*********************************************************************
- Konstruktor
*********************************************************************/
IO::IO() {}

void IO::update() {
  if (DEBUG_LOOP) beginSegment("io");
  
  // pins
  temperaturePcb.update();
  brightnessPcb.update();
  batteryVoltage.update();
  temperatureMd.update();
  buzzer.update();
  indFront.update();
  speaker.update();
  indLeft.update();
  indRight.update();
  indRgb.update();
  indHearbeat.update();
  bluetoothTx.update();
  bluetoothRx.update();
  lineInterrupt.update();
  lineLight.update();
  lineTx.update();
  lineRx.update();
  test1.update();
  test2.update();
  test3.update();
  jumper1.update();
  jumper2.update();
  jumper3.update();
  jumper4.update();
  jumper5.update();
  jumper6.update();
  scl.update();
  sda.update();
  navigationAntennaB.update();
  navigationAntennaA.update();
  navigationAntennaC.update();
  navigationAntennaD.update();
  navigationLight.update();
  ballLight.update();
  ballTouch.update();
  loggerTx.update();
  loggerRx.update();
  loggerTrigger.update();
  m0Speed.update();
  m0Dir1.update();
  m0Dir2.update();
  m0Current.update();
  m1Speed.update();
  m1Dir1.update();
  m1Dir2.update();
  m1Current.update();
  m2Speed.update();
  m2Dir1.update();
  m2Dir2.update();
  m2Current.update();
  m3Speed.update();
  m3Dir1.update();
  m3Dir2.update();
  m3Current.update();
  puiLight.update();
  puiInterrupt.update();
  puiPoti.update();
  kick.update();
  cameraServo.update();
  spiClk.update();
  spiCs.update();
  spiMiso.update();
  spiMosi.update();
  usbTx.update();
  usbRx.update();
  
  // keys
  decreasePage.update();
  increasePage.update();
  selectPage.update();
  decreaseMenu.update();
  increaseMenu.update();
  selectMenu.update();
  testKick.update();
  compassCalibration.update();
  animation.update();
  lineCalibration.update();
  ballTouchCalibration.update();
  start.update();
  stop.update();
  headstart.update();
  motor.update();
  bluetooth.update();
  kicker.update();
  bottom.update();
  turbo.update();

  // shortcuts
  record.update();
  resetProperties.update();
  kickerStart.update();
  kickerStop.update();
  shiftStart.update();
  shiftStop.update();

  // timers
  flat.update();
  onLine.update();
  isHeadstart.update();
  isDodge.update();
  hasBall.update();
  segment.update();
  runtime.update();
  seeBall.update();
  seeGoal.update();
  closeBall.update();
  drift.update();
  ballLeft.update();
  ballRight.update();
  ballCenter.update();
  cameraResponse.update();

  // values
  striker.update();
  state.update();
  stateDirection.update();

  driveAngle.update();
  drivePower.update();
  driveRotation.update();
  driveEnabled.update();

  ball.update();
  ballWidth.update();
  ballArea.update();
  goal.update();
  goalWidth.update();
  goalArea.update();
  
  hasDebugHead.update();

  if (DEBUG_LOOP) endSegment();
}

IO io;