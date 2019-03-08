#include "Reflexion.h"

Reflexion::Reflexion() {}

bool Reflexion::hasBall()   {       return ball;        }
int Reflexion::getValue()   {       return value;       }

void Reflexion::update() {
    if (cycle.off()) {
        if (cali) setThreshold();
        ball = false;
        value = io.ballTouch.get();
        if(value < threshold) ball = true;
        cycle.set();
    }    
    io.ballLight.set(cycle.outsidePeriod(50));
}

void Reflexion::init() {
    threshold = (int)EEPROM.read(REFLEXION_THRESHOLD) * 4;
}

void Reflexion::calibrate() {
    cali = true;
}

void Reflexion::setThreshold() {
    threshold = io.ballTouch.get() - 40;
    EEPROM.write(REFLEXION_THRESHOLD, (byte)threshold / 4);
    cali = false;
}

Reflexion reflexion;