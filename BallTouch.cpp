#include "BallTouch.h"

BallTouch::BallTouch(int pinLed, int pinSensor){
    _pinLed = pinLed;
    _pinSensor = pinSensor;
}

void BallTouch::init(){
    _threshold = (int)EEPROM.read(EEPROM_BALLTOUCH_THRESHOLD) * 4;
    pinMode(_pinLed, OUTPUT);
    pinMode(_pinSensor, INPUT_PULLUP);
}

void BallTouch::calibrate(){
    _threshold = _value - 50;
    EEPROM.write(EEPROM_BALLTOUCH_THRESHOLD, (byte)_threshold / 4);
}

void BallTouch::update(){
    if(_state == LED_ON && millis()-_onTimer > 10){
        turnOff();
        calculate();
    }

    if(_state == LED_OFF && millis()-_offTimer > 10){
        turnOn();
        calculate();
    }

    debug("Threshold: ");
    debug(_threshold);
    debug(" Value: ");
    debug(_value);
}

int BallTouch::getValue(){
    return _value;
}

bool BallTouch::hasBall(){
    return _value > _threshold;
}

void BallTouch::turnOn(){
    _darkValue = analogRead(_pinSensor);
    digitalWrite(_pinLed, HIGH);
    _onTimer = millis();
    _state = LED_ON;
}

void BallTouch::turnOff(){
    _lightValue = analogRead(_pinSensor);
    digitalWrite(_pinLed, LOW);
    _offTimer = millis();
    _state = LED_OFF;
}


void BallTouch::calculate(){
    _value = (_darkValue-_lightValue);
}