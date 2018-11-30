#include "KeyListener.h"

KeyListener::KeyListener(int8_t Xpin) {
    KeyListener(Xpin, preDelay, postDelay, repititionDelay);
}

KeyListener::KeyListener(int8_t Xpin, unsigned long XpreDelay) {
    KeyListener(Xpin, XpreDelay, postDelay, repititionDelay);
}

KeyListener::KeyListener(int8_t Xpin, unsigned long XpreDelay, unsigned long XpostDelay, unsigned long XrepititionDelay) {
    pin = Xpin;
    preDelay = XpreDelay;
    postDelay = XpostDelay;
    repititionDelay = XrepititionDelay;
}

bool KeyListener::stroke() {
    return active && clicks == 1;
}
bool KeyListener::permanent() {
    return active && clicks > 1;
}
bool KeyListener::click() {
    return active;
}

void KeyListener::update() {
    if(digitalRead(pin)) {
        // Knopf ist losgelassen
        cooldownTimer = 0;
        clicks = 0;
    } else {
        // Knopf wird gedrückt
        if (clicks == 0) {
            // Erstmaliges Drücken
            cooldownTimer = millis() + preDelay;
        }
        if (millis() >= cooldownTimer) {
            // Nächster Klick
            clicks++;
            active = true;
            if(clicks == 1) {
                cooldownTimer += postDelay;
            } else {
                cooldownTimer += repititionDelay;
            }
        } else {
            // Warte auf nächsten Klick
            active = false;
        }
    }
}