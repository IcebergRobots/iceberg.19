#ifndef Pin_h
#define Pin_h

#include "core.h"

#define ANALOG false
#define DIGITAL true

class Pin
{
	public:
		Pin(int _pin, byte _mode, bool _digital);
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