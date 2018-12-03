#ifndef Pin_h
#define Pin_h

#include "core.h"

// Pin
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

class Key: public Pin
{
	public:
		/*Key(int _pin) : Pin(int _pin, INPUT_PULLUP, DIGITAL) {
      pin = _pin;
    }
		Key(int _pin, unsigned long _preDelay) : Pin(int _pin, INPUT_PULLUP, DIGITAL) {
      pin = _pin;
	    preDelay = _preDelay;
    }
		Key(int _pin, unsigned long _preDelay, unsigned long _postDelay) : Pin(int _pin, INPUT_PULLUP, DIGITAL) {
      pin = _pin;
	    preDelay = _preDelay;
	    postDelay = _postDelay;
    }*/
		Key(int _pin, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay) : Pin(_pin, INPUT_PULLUP, DIGITAL) {
      pin = _pin;
      preDelay = _preDelay;
      postDelay = _postDelay;
      repititionDelay = _repititionDelay;
    }
		bool stroke();
		bool permanent();
		bool click();
		void update();
	private:
		void cooldown(unsigned long delay);
		int pin = 0;
		bool active = false;
		unsigned long clicks = 0;
		unsigned long preDelay = 0;
		unsigned long postDelay = -1;        // infinity
		unsigned long repititionDelay = -1;  // infinity
		unsigned long cooldownTimer = 0;
};
#endif