#ifndef Pin_h
#define Pin_h

#include "config.h"

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

class Key: public Pin
{
	public:
		Key(int _pin, unsigned long _preDelay = -1, unsigned long _postDelay = -1, unsigned long _repititionDelay = -1) : Pin(_pin, INPUT_PULLUP, DIGITAL) {
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
		unsigned long postDelay = 0;        // infinity
		unsigned long repititionDelay = 0;  // infinity
		unsigned long cooldownTimer = 0;
};

#define MUTE_KEYS true
#define FIRE_KEYS false
/*
class Shortcut: public Key
{
	public:
		Shortcut(Pin *_keys, bool _muteKeys) : Key(int _pin) {
    }
		Shortcut(Pin *_keys, bool _muteKeys, unsigned long _preDelay) : Key(int _pin, unsigned long _preDelay) {
    }
		Shortcut(Pin *_keys, bool _muteKeys, unsigned long _preDelay, unsigned long _postDelay) : Key(int _pin, unsigned long _preDelay, unsigned long _postDelay) {
    }
		Shortcut(Pin *_keys, bool _muteKeys, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay) : Key(int _pin, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay) {
    }
    void update();  // => set fix value from Key.get() objects
	private:
		Pin keys[];
};*/
#endif