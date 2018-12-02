#include "Pin.h"

Pin::Pin(int _pin, byte _mode, bool _digital) {
  pin = _pin;
  mode = _mode;
  digital = _digital;
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