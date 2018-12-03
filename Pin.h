#ifndef Pin_h
#define Pin_h

#include "core.h"

#define ANALOG 0
#define DIGITAL 1
#define PWM 2

class Pin
{
	public:
		Pin(int _pin, byte _mode, byte _type);
		void set(int _value);
		byte get();
		void update();
		byte getPin();
	private:
		int pin = 0;
		byte mode = 0;	// OUTPUT, INPUT, INPUT_PULLUP
		byte value = 0;
		bool digital = true;
};
#endif