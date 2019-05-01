#ifndef Led_hpp
#define Led_hpp

#include "Config.hpp"

#include <Adafruit_NeoPixel.h>

class Led
{
  public:
    Led();

    void heartbeat();
    void led();
    void set();
    void start();
    void hymne();
    void cancel();
    bool isAnimation();
    unsigned long lastAnimation();

    void showCalibration();

  private:
    void showState(Adafruit_NeoPixel & board, byte pos, byte state, bool showRed);
    void showState(Adafruit_NeoPixel & board, byte pos, byte state);
    void wheelBoard(Adafruit_NeoPixel & board, int boardLength, int offset);
    void setBoard(Adafruit_NeoPixel & board, int boardLength, uint32_t color);
    uint32_t wheelToColor(Adafruit_NeoPixel & board, byte pos);
    void myTone(unsigned int frequency, unsigned long duration, unsigned long pause);

    unsigned long timer = 0; // Position in der Animation
};

#endif
