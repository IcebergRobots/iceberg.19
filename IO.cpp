#include "IO.h"

Pin::Pin(byte _pin, byte _mode, byte _type) {
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
}
Pin::Pin() {
  mode = INPUT;
  type = VIRTUAL;
}

void Pin::set(int _value) {
  value = _value;
  if(mode == OUTPUT) {
    switch (type) {
      case ANALOG:
      case DIGITAL:
      case PWM:
        if(digital) {
          value = (value != 0);
          digitalWrite(pin, value);
        } else {
          value = constrain(value, 0, 255);
          analogWrite(pin, value);
        }
        break;

      case PUI:
        value = (value != 0);
        pui.set(pin, value);
        break;

      case VIRTUAL:
      default:
        break;
    }
  }
}

byte Pin::get() {
  return value;
}

bool Pin::on() {
  return value != 0;
}

bool Pin::off() {
  return value == 0;
}

void Pin::update() {
  switch (type)
  {
    case ANALOG:
    case DIGITAL:
    case PWM:
      if (digital) value = digitalRead(pin);
	    else value = analogRead(pin);
    break;
    case PUI:
      pui.get(pin);
    break;
  }
  if(mode == INPUT_PULLUP && type != VIRTUAL) value = !value;
}

byte Pin::getPin() {
	return pin;
}




/******************************************************************************
                                  click
                 ┌─────────┬────────┴──────┬───────────────┬─╌                                                
              stroke   permanent       permanent       permanent    
      on╔════════╪═════════╪═══════════════╪═══════════════╪═════ ... ═╗
Button  ║        ┊         ┊               ┊               ┊           ║
     off║        ┊         ┊               ┊               ┊           ║
════════╝        ┊postDelay┊               ┊               ┊           ╚══════                
        ┊preDelay┊         ┊repititionDelay┊repititionDelay┊                                             

******************************************************************************/

Key::Key(byte _pin, byte _type, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay)
 : Pin(_pin, INPUT_PULLUP, _type) {
  preDelay = _preDelay;
  postDelay = _postDelay;
  repititionDelay = _repititionDelay;
}

bool Key::stroke() {
	return active && clicks == 1;
}
bool Key::permanent() {
	return active && clicks > 1;
}
bool Key::click() {
	return active;
}

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

void Key::cooldown(unsigned long delay) {
	if(delay + 1 == 0) cooldownTimer = -1;
	else cooldownTimer = millis() + delay;
}



Shortcut::Shortcut(Key **_keys, byte _keysLength, bool _muteKeys, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay)
 : Key(0, VIRTUAL, _preDelay, _postDelay, _repititionDelay) {
  keys = _keys;
  keysLength = _keysLength;
  muteKeys = _muteKeys;
}

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




Pui::Pui() {}

void Pui::init() {
  beginSegment("pui");
  I2c.write(ADDRESS, A_PINMODE, 0x00); // set OUTPUT
  I2c.write(ADDRESS, B_PINMODE, 0xFF);  // set INPUT
  I2c.write(ADDRESS, B_VALUE, 0xFF);    // set INPUT_PULLUP
  endSegment();
}

void Pui::set(byte pin, bool value) {
  if(pin < 8) {
    bitWrite(a, pin, value);
    I2c.write(ADDRESS, A_VALUE, a);
  }
}

bool Pui::get(byte pin) {
  if(pin < 8) return bitRead(a, pin);
  else return bitRead(b, pin-8);
}

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