#include "Pin.h"

Pin::Pin(int _pin, byte _mode, byte _type) {
  pin = _pin;
  mode = _mode;
  digital = (_mode == OUTPUT && _type == DIGITAL) || (_mode != OUTPUT && _type != ANALOG);
  pinMode(pin, mode);
}

void Pin::set(int value) {
  if(mode == OUTPUT) {
	if(pin < 0) {
	  // I2C Expander Pin
	  /*byte address = pin - INT16_T_MIN; // Decode pin address
	  I2c.read(address, numberBytes);
	  I2c.receive()
	  http://dsscircuits.com/articles/arduino-i2c-master-library
	  https://tronixstuff.com/2011/08/26/tutorial-maximising-your-arduinos-io-ports/
	  https://cdn-shop.adafruit.com/datasheets/mcp23017.pdf
	  http://www.gammon.com.au/i2c
	  */
	}
	if(digital) digitalWrite(pin, value);
	else analogWrite(pin, constrain(value, 0, 255));
  }
}

byte Pin::get() {
  return value;
}

void Pin::update() {
  if (pin < 0) {
	/*// I2C Expander Pin
	byte address = pin - INT16_T_MIN; // Decode pin address
	  I2c.read(address, numberBytes);
	  I2c.receive()
	  bitRead
	  */
  } else {
	if (digital) value = digitalRead(pin);
	else value = analogRead(pin);
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