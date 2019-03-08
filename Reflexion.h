#ifndef Reflexion_h
#define Reflexion_h

#include "IO.h"

class Reflexion
{
    public:
    Reflexion();

    void update();
    void init();
    void calibrate();
    
    bool hasBall();
    int getValue();

    private:
    Timer cycle = Timer(55);
    bool ball = false;
    int threshold = 0;
    bool cali = false;
    int value = 0;

    void setThreshold();
};

extern Reflexion reflexion;

#endif