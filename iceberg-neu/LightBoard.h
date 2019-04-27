#ifndef LightBoard_h
#define LightBoard_h

#include "IO.h"
#include "Demand.h"
#include <Adafruit_NeoPixel.h>

#define STATE_DEFAULT 0
#define STATE_ACTIVE 1
#define STATE_OK 2
#define STATE_WARNING 3
#define STATE_ERROR 4

class LightBoard : public Adafruit_NeoPixel, public Demand
{
  public:
    LightBoard(int numPixels, int pin, unsigned long lockedPeriod=0, unsigned long cooldownPeriod=0);
    void setAllColor(unsigned long color);
    void setAllColor(byte red, byte green, byte blue);
    void setAllWheel(int offset);
    void setPixelState(byte pos, byte state = STATE_DEFAULT);

    bool isEnabled();

  // private:
    unsigned long wheelToColor(byte pos);
};

#endif
