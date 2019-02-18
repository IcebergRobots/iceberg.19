#ifndef Light_h
#define Light_h

#include "IO.h"
#include "Demand.h"
#include <Adafruit_NeoPixel.h>

class Light : public Demand
{
  public:
    Light();
    void init();
    void light();
    
    bool isEnabled();

  private:
    void showState(Adafruit_NeoPixel & board, byte pos, byte state, bool hideRed=false);
    void wheelBoard(Adafruit_NeoPixel & board, int offset);
    void setBoard(Adafruit_NeoPixel & board, uint32_t color);
    uint32_t wheelToColor(Adafruit_NeoPixel & board, byte pos);
    Adafruit_NeoPixel puiBoard = Adafruit_NeoPixel(12, io.puiLight.getPin(), NEO_GRB + NEO_KHZ800);

};
extern Light light;

#endif
