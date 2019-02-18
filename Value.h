#ifndef Value_h
#define Value_h

#include "Pui.h"
#include "Container.h"

// States
#define OFF     0
#define ON      1
#define FALLING 2
#define RISING  3
#define STROKE  4
#define FURTHER 6

// Processing
#define LIMITS     0
#define MODULATION 1
#define BOOLEAN    2

// Debug debug
#define DEBUG_ENABLE      0
#define DEBUG_ON_CHANGE   1
#define DEBUG_ON_REASON   2
#define DEBUG_FOR_PLOTTER 3
#define DEBUG_PIN         4
#define DEBUG_TIME        5
#define DEBUG_VALUE       6
#define DEBUG_REASON      7

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
    Value(byte processing=LIMITS, int min=INT16_T_MIN, int max=INT16_T_MAX);
    void setLimits(int min=INT16_T_MIN, int max=INT16_T_MAX); //huhu
    void setModulation(int min, int max);

    // tick
    void update();

    // interact
    void now(bool mute=false);
    void muteSet(int _value);
    void set(int _value, byte pin=INF);
    void set(int _value, String reason, byte pin=INF);
    void add(int _summand=1);
    void mul(float _factor);

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
    String periodStr(unsigned int minLength=0, unsigned int maxLength=INF, bool sign=false);

    // debug
    void showDebug(byte type, bool enable=true);
    void startDebug();
    void stopDebug();
    void resetDebug();

    void setElementType(byte type);
    byte getElementType();

  private:
    bool isDebug(byte type=DEBUG_ENABLE);
    void sendDebug(byte pin=INF);
    void sendDebug(String reason, byte pin=INF);
    String prepareDebug(byte pin);

    byte elementType = VALUE;
    int value = 0;
    int a = 0;  // in case of modulation: upper limit
                // in case of limits: lower limit
    int b = 0;  // in case of modulation: lower limit
                // in case of limits: upper limit
    unsigned long eventTimer = 0; // time of last event
    byte state = OFF; // OFF, ON, FALLING, RISING
    byte debugSettings = B11000010;
};

#endif