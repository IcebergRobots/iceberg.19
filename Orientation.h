#ifndef ORIENTATION_h
#define ORIENTATION_h

#include "IO.h"
#include "Demand.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

class Orientation : private Adafruit_BNO055, public Demand
{
  public:
    Orientation();
    void init();
    void update();

  private:
    Adafruit_BNO055 bno = Adafruit_BNO055(55);
};
extern Orientation orientation;

#endif