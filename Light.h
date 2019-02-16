#ifndef Light_h
#define Light_h

#include "IO.h"
#include "Demand.h"
#include <Adafruit_NeoPixel.h>

class Light : public Adafruit_NeoPixel, public Demand
{
  public:
    Light(int numPixels, Pin &pin);
    void setAllColor(unsigned long color);
    void setAllColor(byte red, byte green, byte blue);
    void setAllWheel(int offset);
    void setPixelState(byte pos, byte state, bool hideRed);

  private:
    unsigned long wheelToColor(byte pos);

};
extern Light puiBoard;

#endif
