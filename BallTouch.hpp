#ifndef BallTouch_hpp
#define BallTouch_hpp

#include "Config.hpp"

#define LED_OFF false
#define LED_ON true

class BallTouch{
    public:
        BallTouch(int pinLed, int pinSensor);

        void init();
        void calibrate();
        void update();

        int getValue();

        bool hasBall();

    private:
        int _pinLed;
        int _pinSensor;
        int _value;
        int _threshold = 0;

        int _darkValue;
        int _lightValue;

        unsigned long _offTimer = 0;
        unsigned long _onTimer = 0;

        bool _state = LED_OFF;

        void turnOn();
        void turnOff();
        void calculate();  
};

#endif