#ifndef Pin_h
#define Pin_h

#include "config.h"

// Mode
#define ANALOG 0
#define DIGITAL 1
#define PWM 2
#define PUI 3
#define VIRTUAL 4

class Pin
{
	public:
		Pin(byte _pin, byte _mode, byte _type);
    Pin();
		void set(int _value);
		byte get();
		void update();
		byte getPin();
	private:
		byte pin = 0;
		byte mode = 0;  // OUTPUT, INPUT, INPUT_PULLUP
		byte type = 0;  // ANALOG, DIGITAL, PWM, PUI, VIRTUAL
    int value = 0;
		bool digital = 0;
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
		Key(byte _pin, byte _type, unsigned long _preDelay = -1, unsigned long _postDelay = -1, unsigned long _repititionDelay = -1);
    /*Key(unsigned long _preDelay = -1, unsigned long _postDelay = -1, unsigned long _repititionDelay = -1) : Pin() {
      preDelay = _preDelay;
      postDelay = _postDelay;
      repititionDelay = _repititionDelay;
    }*/
		bool stroke();
		bool permanent();
		bool click();
		void update();
	private:
		void cooldown(unsigned long delay);
    bool active;
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
		Shortcut(Key *_keys, bool _muteKeys) : Key(int 0, ) {
    }
		Shortcut(Key *_keys, bool _muteKeys, unsigned long _preDelay) : Key(int _pin, unsigned long _preDelay) {
    }
		Shortcut(Key *_keys, bool _muteKeys, unsigned long _preDelay, unsigned long _postDelay) : Key(int _pin, unsigned long _preDelay, unsigned long _postDelay) {
    }
		Shortcut(Key *_keys, bool _muteKeys, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay) : Key(int _pin, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay) {
    }
    void update();  // => set fix value from Key.get() objects
	private:
		Pin keys[];
};*/
#endif