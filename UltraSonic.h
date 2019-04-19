#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Demand.h"
#include "IO.h"

class Ultrasonic : public Demand {
public:
    Ultrasonic();
    void update();
    void init();
    void position();

    int frontLeft();
    int left();
    int back();
    int right();
    int frontRight();

    int left2();
    int right2();

    int left3();
    int right3();

    int front();

    int getx();
    int gety();

private:
    void fetch();
    bool isEnabled();
    bool validate();

    int x = 0;
    int y = 0;

    int distance[5] = {0, 0, 0, 0, 0};
    int echo2[2] = {0, 0};
    int echo3[2] = {0, 0};
    const byte addresses[5] PROGMEM = {I2C_US_FRONT_LEFT, I2C_US_LEFT, I2C_US_BACK, I2C_US_RIGHT, I2C_US_FRONT_RIGHT}; 
};

extern Ultrasonic us;

#endif