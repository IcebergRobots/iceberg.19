#include "Reflexion.h"

Reflexion::Reflexion() {}

int Reflexion::getValue()   {
    return value;
}

void Reflexion::update() {
    io.ballLight.set(light.on());

    if (isLightPhase && light.off()) {
        isLightPhase = false;
        withLight = io.ballTouch.get();
        dark.set();
    } else if (!isLightPhase && dark.off()) {
        isLightPhase = true;
        withDark = io.ballTouch.get();
        light.set();
    }
    value = withDark - withLight;
    if (value > threshold) io.hasBall.set();
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
    threshold = value + 100;
    EEPROM.write(REFLEXION_THRESHOLD, (byte)threshold / 4);
    cali = false;
}

Reflexion reflexion;