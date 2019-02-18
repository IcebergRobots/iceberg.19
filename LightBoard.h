#ifndef LightBoard_h
#define LightBoard_h

#include "IO.h"
#include "Demand.h"
#include <Adafruit_NeoPixel.h>

class LightBoard : public Adafruit_NeoPixel, public Demand
{
  public:
    LightBoard(int numPixels, Pin &pin, unsigned long lockedPeriod=0, unsigned long cooldownPeriod=0);
    void setAllColor(unsigned long color);
    void setAllColor(byte red, byte green, byte blue);
    void setAllWheel(int offset);
    void setPixelState(byte pos, byte state, bool hideRed);

    bool isEnabled();

  private:
    unsigned long wheelToColor(byte pos);
};

#endif
