#ifndef Compass_hpp
#define Compass_hpp

#include "Config.hpp"

#define I2C_COMPASS_ADDRESS

class Compass{
    public:
        Compass();
        void init();
        void update();

        void calibrate();

        int getHeading();
        int getPitch();
        int getRoll();
    private:
        int _heading;
        int _pitch;
        int _roll;
};

#endif