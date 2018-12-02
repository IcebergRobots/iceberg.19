#ifndef Pin_h
#define Pin_h

#include "Core.h"

class Pin
{
  public:
    Pin(int _pin, byte _pinMode, bool _digital);
    void set(int _value);
    byte get();
  private:
    int pin = 0;
    byte pinMode = 0;
    byte value = 0;
    bool digital = true;
};
#endif