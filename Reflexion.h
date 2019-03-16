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
    
    int getValue();

    bool isEnabled();

    private:
    Timer light = Timer(15);
    Timer dark = Timer(50);
    bool isLightPhase = false;
    int threshold = 0;
    bool cali = false;
    
    int withDark = 0;
    int withLight = 0;
    int value = 0;

    void setThreshold();
};

extern Reflexion reflexion;

#endif