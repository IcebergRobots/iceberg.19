#ifndef LightBoard_h
#define LightBoard_h

#include "IO.h"
#include "Demand.h"
#include "FastLED.h"

#define STATE_DEFAULT 0
#define STATE_ACTIVE 1
#define STATE_OK 2
#define STATE_WARNING 3
#define STATE_ERROR 4

#define MAX_NUM_LEDS 12 + 40 + 8

CRGB ledStrips[MAX_NUM_LEDS];
int startingIndexCounter = 0;
extern CLEDController CFastLED;

class LightBoard : public Demand
{
  public:
    LightBoard(int numPixels, int pin, unsigned long lockedPeriod=0, unsigned long cooldownPeriod=0);
    void setAllColor(unsigned long color);
    void setAllColor(byte red, byte green, byte blue);
    void setAllWheel(int offset);
    void setPixelState(byte pos, byte state = STATE_DEFAULT);

    void setPixelColor(byte pos, byte _r, byte _g, byte _b);
    void show();
    void setBrightness(byte b);


    bool isEnabled();

  // private:
    unsigned long wheelToColor(byte pos);
    byte numPixels();

  private:
    byte addressOffset;
    byte brightness = 255;
    byte numLEDs;
};


#endif
