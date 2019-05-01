#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Config.h"

#define I2C_US_FRONT_LEFT 112
#define I2C_US_LEFT 113
#define I2C_US_BACK 114
#define I2C_US_RIGHT 115
#define I2C_US_FRONT_RIGHT 116

class Ultrasonic
{
  public:
    Ultrasonic();
    int right();
    int front();
    int left();
    int back();
    
    int frontLeft();
    int frontRight();

    int left2();
    int right2();

    int left3();
    int right3();

    bool check();

    void update();

    void init();

  private:
    void fetch();

    int distance[5] = {0, 0, 0, 0, 0};
    int echo2[2] = {0, 0};
    int echo3[2] = {0, 0};

    bool fetched = true;
    unsigned long lastMeasurement = 0;
    const byte addresses[5] PROGMEM = {I2C_US_FRONT_LEFT, I2C_US_LEFT, I2C_US_BACK, I2C_US_RIGHT, I2C_US_FRONT_RIGHT}; 
};

#endif
