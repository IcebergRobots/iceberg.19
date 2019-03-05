#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Demand.h"

class Ultrasonic : public Demand {
public:
    Ultrasonic();
    void update();
    void init();

    int frontLeft();
    int left();
    int back();
    int right();
    int frontRight();

    int front();

private:
    void fetch();
    bool isEnabled();

    int distance[5] = {0, 0, 0, 0, 0};
    byte addresses[5] = {I2C_US_FRONT_LEFT, I2C_US_LEFT, I2C_US_BACK, I2C_US_RIGHT, I2C_US_FRONT_RIGHT}; 
};

extern Ultrasonic us;

#endif