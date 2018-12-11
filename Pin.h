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
		bool digital = false;
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
    Key(byte _pin, byte _type, unsigned long _preDelay=-1, unsigned long _postDelay=-1, unsigned long _repititionDelay=-1);
		bool stroke();
		bool permanent();
		bool click();
		void update();
	private:
		void cooldown(unsigned long delay);
    bool active = false;
		unsigned long clicks = 0;
		unsigned long preDelay = -1;         // infinity
		unsigned long postDelay = -1;        // infinity
		unsigned long repititionDelay = -1;  // infinity
		unsigned long cooldownTimer = 0;
};

#define MUTE_KEYS true
#define FIRE_KEYS false

class Shortcut: public Key
{
	public:
		Shortcut(Key **_keys, byte _keysLength, bool _muteKeys, unsigned long _preDelay=-1, unsigned long _postDelay=-1, unsigned long _repititionDelay=-1);
    void update();  // => set fix value from Key.get() objects
	private:
		Key **keys;
    byte keysLength = 0;
    bool muteKeys = false;
};

class Pui 
{
  public:
    Pui();
    void init();
    void set(byte pin, bool value);
    bool get(byte pin);
    void update();
  private:
    static const byte ADDRESS = 0x20;
    static const byte A_PINMODE = 0x00;
    static const byte B_PINMODE = 0x01;
    static const byte A_VALUE = 0x12;
    static const byte B_VALUE = 0x13;
    byte a = 0;
    byte b = 0;
};

extern Pui pui;

#endif