#include "Reflexion.h"

Reflexion::Reflexion() {}

int Reflexion::getValue()
{
    return value;
}

void Reflexion::update()
{
    if (isEnabled())
    {
        if (DEBUG_LOOP)
            beginSegment("ref");
        io.ballLight.set(light.on());

        if (isLightPhase && light.off())
        {
            isLightPhase = false;
            withLight = io.ballTouch.get();
            dark.now();
        }
        else if (!isLightPhase && dark.off())
        {
            isLightPhase = true;
            withDark = io.ballTouch.get();
            light.now();
        }
        value = withDark - withLight;
        if (value > threshold)
            io.hasBall.now();
        if (cali)
            setThreshold();
        if (DEBUG_LOOP)
            endSegment();
    }
}

void Reflexion::init()
{
    light.now();
    threshold = (int)EEPROM.read(REFLEXION_THRESHOLD) * 4;
}

void Reflexion::calibrate()
{
    cali = true;
}

void Reflexion::setThreshold()
{
    threshold = value + 100;
    EEPROM.write(REFLEXION_THRESHOLD, (byte)threshold / 4);
    cali = false;
}

bool Reflexion::isEnabled()
{
    return REFLEXION_ENABLED;
}

Reflexion reflexion;