#include "Reflexion.h"
//TODO kein daueerhaftes Licht(Timer)
//TODO analogRead ersetzen?

bool Reflexion::hasball() {return ball;}

void Reflexion::update() {
    ball = analogRead(io.ballTouch);
}

void Reflexion::init() {
    digitalWrite(io.ballLight, HIGH);
}

Reflexion reflexion;