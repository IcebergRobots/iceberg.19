#ifndef Light_h
#define Light_h

#include "basic.h"

class Light
{
  public:
    Light();
    void light();

  private:
    void showState(Adafruit_NeoPixel & board, byte pos, byte state);
    void showState(Adafruit_NeoPixel & board, byte pos, byte state, bool hideRed);
    void wheelBoard(Adafruit_NeoPixel & board, int offset);
    void setBoard(Adafruit_NeoPixel & board, uint32_t color);
    uint32_t wheelToColor(Adafruit_NeoPixel & board, byte pos);
    Adafruit_NeoPixel pui = Adafruit_NeoPixel(12, io.puiLight.getPin(), NEO_GRB + NEO_KHZ800);

};
#endif
