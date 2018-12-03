#include "Pin.h"

Pin::Pin(byte _pin, byte _mode, byte _type) {
  pin = _pin;
  mode = _mode;
  switch (mode) {
    case PWM:
      digital = (_type != OUTPUT);
    case DIGITAL:
    case PUI:
    case VIRTUAL:
      digital = true;
      break;
  }
  pinMode(pin, mode);
}

void Pin::set(int _value) {
  value = _value;
  if(mode == OUTPUT) {
    switch (mode) {
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
	if(digitalRead(pin)) {
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