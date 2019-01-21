#include "IO.h"

/*****************************************************
  create a timer
  @param _surviveTime:
  - if positiv:  leave output active for a delay
  - if negative: activate output only after delay
*****************************************************/
Timer::Timer(long _surviveTime=0) {
  surviveTime = _surviveTime;
}

/*****************************************************
  set survive time
  @param _surviveTime:
  - if positiv:  leave output active for a delay
  - if negative: activate output only after delay
*****************************************************/
void Timer::setSurviveTime(long surviveTime) {
  surviveTime = _surviveTime;
}

/*****************************************************
  refresh timer
  - set timer to current time
*****************************************************/
void Timer::now() {
  timer = millis();
}

/*****************************************************
  is the timer on?
*****************************************************/
bool Timer::get() {
  return active;
}
bool Timer::on() {
  return active;
}

/*****************************************************
  is the timer off?
*****************************************************/
bool Timer:off() {
  return !active;
}

/*****************************************************
  is the timer active?
*****************************************************/
bool Timer::on() {
  return active;
}


/*****************************************************
  calculate timings to update active flag
*****************************************************/
void Timer::update(bool require) {
  if(surviveTime >= 0) active = require && millis() <= timer + surviveTime;
  else active = require && millis() >= timer - surviveTime; 
}


400 250+100=350 true

unsigned long Timer:since() {
  if(active) return 0;
  else if(surviveTime >= 0) return millis() - timer - surviveTime;
  else active = require && millis() >= timer - surviveTime; 
}

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
Value::Value(bool processing, int min, int max) {
  if(processing == LIMITS) setLimits(min, max);
  else setModulation(min, max);
}

/*****************************************************
  set a new value process it
  @param _value: new value
  - modulate or limit the value
*****************************************************/
void Value::set(int _value) {
  if(a <= b) value = constrain(_value, a, b); // limit
  else value = circulate(_value, a, b);           // modulate
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
}

/*****************************************************
  return value
*****************************************************/
int Value::get() {
  return value;
}

/*****************************************************
  is value active?
*****************************************************/
bool Value::on() {
  return value != 0;
}

/*****************************************************
  is value passive?
*****************************************************/
bool Value::off() {
  return value == 0;
}

/*****************************************************
  convert number to String
*****************************************************/
String Value::str() {
  return String(value);
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
  if(mode != OUTPUT) {
    switch (type)
    {
      case VIRTUAL:
        return;
      case ANALOG:
      case DIGITAL:
      case PWM:
        if (digital) set(digitalRead(pin));
        else Pin::set(analogRead(pin));
      break;
      case PUI:
        pui.get(pin);
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
  @param _preDelay: delay befor the first click
  @param _postDelay: delay after the first click
  @param _repititionDelay: delay after second or later click
  - see header file for visualisation
*****************************************************/
Key::Key(byte _pin, byte _type, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay)
 : Pin(_pin, INPUT_PULLUP, _type) {
  preDelay = _preDelay;
  postDelay = _postDelay;
  repititionDelay = _repititionDelay;
}

/*****************************************************
  is there a first click?
*****************************************************/
bool Key::stroke() {
	return active && clicks == 1;
}

/*****************************************************
  is there a second or later click?
*****************************************************/
bool Key::permanent() {
	return active && clicks > 1;
}

/*****************************************************
  is there any click?
*****************************************************/
bool Key::click() {
	return active;
}

/*****************************************************
  read the arduino pins and process it to detect clicks
*****************************************************/
void Key::update() {
  Pin::update();
	if(off()) {
		// Knopf ist losgelassen
		cooldownTimer = 0;
		clicks = 0;
	} else {
		// Knopf wird gedrückt
		if (cooldownTimer == 0) cooldown(preDelay); // Erstmaliges Drücken
		if (millis() >= cooldownTimer) {
			// Nächster Klick
			clicks++;
			active = true;
			if(clicks == 1) cooldown(postDelay);
			else cooldown(repititionDelay);
		} else active = false; // Warte auf nächsten Klick
	}
}

/*****************************************************
  ignore click for the next milliseconds
  @param delay: cooldown time
*****************************************************/
void Key::cooldown(unsigned long delay) {
	if(delay + 1 == 0) cooldownTimer = -1;
	else cooldownTimer = millis() + delay;
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
  @param _preDelay: delay befor the first shortcut click
  @param _postDelay: delay after the first shortcut click
  @param _repititionDelay: delay after second or later shortcut click
*****************************************************/
Shortcut::Shortcut(Key **_keys, byte _keysLength, bool _muteKeys, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay)
 : Key(0, VIRTUAL, _preDelay, _postDelay, _repititionDelay) {
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
  Key::update(); // is this shortcut active (stroke, permanent, click)?
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
  lightBeamTx.update();
  lightBeamRx.update();
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
  lightBeamCalibration.update();
  start.update();
  stop.update();
  headstart.update();
  motor.update();
  bluetooth.update();
  kicker.update();
  bottom.update();
  debug.update();
  
  lifted.update();
  onLine.update();
  isHeadstart.update();
  isDodge.update();
  hasBall.update();
  seeBall.update();
  seeGoal.update();
  closeBall.update();
  
  record.update();
  resetProperties.update();
  kickerStart.update();
  kickerStop.update();

  if (DEBUG_LOOP) endSegment();
}

IO io = IO();