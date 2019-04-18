#ifndef Value_h
#define Value_h

#include "core.h"
#include "Container.h"
#include "Adafruit_MCP23017.h"

// States
#define OFF     0
#define ON      1 // on change: -1
#define FALLING 2 // on change: -2
#define RISING  3 // on change: -3

// Processing
#define LIMITS     0
#define MODULATION 1
#define BOOLEAN    2

// Values
#define LEFT  false
#define RIGHT true
#define INF -1 // infinity

// Element type
#define VALUE    0
#define TIMER    1
#define PIN      2
#define KEY      3
#define SHORTCUT 4

/*****************************************************
  class Value
  1) supports modulation:      2) supports limits:                  
  - values are saved circular  - values are saved limited                      
  - eg:                        - eg:
      setModulation(0, 9);         setLimits(0, 9);                   
      set(11) => 1                 set(11) => 9           
      set(4)  => 4                 set(4)  => 4           
      set(-1) => 9                 set(-1) => 0           

*****************************************************/
class Value : public Container
{
  public:
    // configutate
    Value(byte processing=LIMITS, int _min=INT16_T_MIN, int _max=INT16_T_MAX);
    void setLimits(int _min=INT16_T_MIN, int _max=INT16_T_MAX); //huhu
    void setModulation(int _min, int _max);

    // tick
    void update();

    // interact
    void now();
    void abort();
    bool setWithoutEvent(int _value);
    void set(int _value, byte pin=INF);
    void add(int _summand=1);
    void mul(float _factor);
    void toggle();
    void setLow();
    void setHigh();

    // read
		int get();
    bool on();
    bool off();
    bool right(int tolerance=0);
    bool left(int tolerance=0);
    bool center(int tolerance=0);
    bool is(int comparison);
    bool no(int comparison);
    String str(unsigned int minLength=0, unsigned int maxLength=INF, bool sign=false);

    // read change
    bool falling();
    bool rising();
    bool change();

    // events
    bool ever();
    bool never();
    unsigned long period();
    bool outsidePeriod(unsigned long min);
    bool insidePeroid(unsigned long max);

    void setElementType(byte type);
    byte getElementType();

  private:
    void setState(byte s);
    char getState();
    bool timerValid();
    byte elementType = VALUE;
    int value = 0;
    int a = 0;  // in case of modulation: upper limit
                // in case of limits: lower limit
    int b = 0;  // in case of modulation: lower limit
                // in case of limits: upper limit
    unsigned int eventTimer = 0; // 0: no event jet, 1: event canceled, >1: time of last event
    char state = OFF; // OFF, ON, FALLING, RISING, OFF_CHANGE, ON_
};

#endif