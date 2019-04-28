#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Config.h"

#define CACHE_SIZE 4 // Länge des Input Byte Buffers

class Ultrasonic
{
  public:
    Ultrasonic();
    byte right();
    byte front();
    byte left();
    byte back();

    bool check();

    void update();

  private:
    byte distanceRight = 0;
    byte distanceFront = 0;
    byte distanceLeft  = 0;
    byte distanceBack  = 0;
};

#endif
