#include "Reflexion.h"

Reflexion::Reflexion() {}

bool Reflexion::hasBall()   {       return ball;        }
int Reflexion::getValue()   {       return value;       }

void Reflexion::update() {
    io.ballLight.set(light.on());
    ball = false;

    if (isLightPhase && light.off()) {
        isLightPhase = false;
        //ball = false;
        withLight = io.ballTouch.get();
        dark.set();
    } else if (!isLightPhase && dark.off()) {
        isLightPhase = true;
        withDark = io.ballTouch.get();
        light.set();
    }
    value = withDark - withLight;
    if (value > threshold) ball = true;
    if (cali) setThreshold();

}

void Reflexion::init() {
    light.set();
    threshold = (int)EEPROM.read(REFLEXION_THRESHOLD) * 4;
}

void Reflexion::calibrate() {
    cali = true;
}

void Reflexion::setThreshold() {
    threshold = value + 10;
    EEPROM.write(REFLEXION_THRESHOLD, (byte)threshold / 4);
    cali = false;
}

Reflexion reflexion;