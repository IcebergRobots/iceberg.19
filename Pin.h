#ifndef Pin_h
#define Pin_h

#include "Value.h"

// Mode
#define ANALOG 0
#define DIGITAL 1
#define PWM 2
#define PUI 3
#define VIRTUAL 4

class Pin : public Value
{
  public:
	Pin(byte _pin, byte _mode, byte _type);
	void set(int _value);
	void set(int _value, String reason);
	void set();
	void temp(int _value);
	void temp(int _value, String reason);
	void update();
	byte getPin();

  private:
	byte pin = 0;  // pin address
	byte mode = 0; // OUTPUT, INPUT, INPUT_PULLUP
	byte type = 0; // ANALOG, DIGITAL, PWM, PUI, VIRTUAL
	bool digital = false;
};

#endif