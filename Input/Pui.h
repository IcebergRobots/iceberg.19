#ifndef Pui_h
#define Pui_h

#include "../core.h"
#include <I2C.h>

class Pui 
{
  public:
    Pui();
    void init();
    void set(byte pin, bool value);
    bool get(byte pin);
    void update();
  private:
    static const byte ADDRESS = 0x20;
    static const byte A_PINMODE = 0x00;
    static const byte B_PINMODE = 0x01;
    static const byte A_VALUE = 0x12;
    static const byte B_VALUE = 0x13;
    byte a = 0;
    byte b = 0;
};
extern Pui pui;

#endif