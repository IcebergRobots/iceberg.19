#include "Pin.h"

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
        /* I2C Expander Pin
        I2c.read(pin, numberBytes);
        I2c.receive()
        http://dsscircuits.com/articles/arduino-i2c-master-library
        https://tronixstuff.com/2011/08/26/tutorial-maximising-your-arduinos-io-ports/
        https://cdn-shop.adafruit.com/datasheets/mcp23017.pdf
        http://www.gammon.com.au/i2c
        */
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

void Pin::update() {
  switch (mode)
  {
    case ANALOG:
    case DIGITAL:
    case PWM:
      if (digital) value = digitalRead(pin);
	    else value = analogRead(pin);
      break;
    case PUI:
      /* I2C Expander Pin
        I2c.read(pin, numberBytes);
        I2c.receive()
        */
      break;
  }
}

byte Pin::getPin() {
	return pin;
}





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
	if(get()) {
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



