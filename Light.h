#ifndef Light_h
#define Light_h

#include "IO.h"
#include "Demand.h"
#include <Adafruit_NeoPixel.h>

class Light : public Adafruit_NeoPixel, public Demand
{
  public:
    Light(int numPixels, Pin *pin);
    setAllColor(unsigned long color);
    setAllColor(byte red, byte green, byte blue);
    setAllWheel(int offset);
    setPixelState(byte pos, byte state, bool hideRed);

  private:
    unsigned long wheelToColor(Adafruit_NeoPixel & board, byte pos);

};
extern Light puiBoard;

#endif
