#ifndef ORIENTATION_h
#define ORIENTATION_h

#include "IO.h"
#include "Demand.h"
#include <Wire.h>
#include "BNO055_support.h"    //Contains the bridge code between the API and Arduino

class Orientation : public Demand
{
  public:
    Orientation();
    void init();
    void update();
    
    bool isEnabled();

  private:
    struct bno055_t bno;
};
extern Orientation orientation;

#endif
