#ifndef Compass_hpp
#define Compass_hpp

#include "Config.hpp"

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>

#define I2C_COMPASS_ADDRESS 55
#define FLAT_ANGLE          15

class Compass{
    public:
        Compass();
        void init();
        void update();

        void restoreOffsets();

        void setStartHeading();
        void setStartHeading(int angle);
        void calibrate();

        int getHeading();
        int getPitch();
        int getRoll();

        void getCalibration(byte *system, byte *gyro, byte *accel, byte *mag);
    // private:
        int _startHeading = 0;

        int _heading;
        int _pitch;
        int _roll;

        sensors_event_t _event;

        Adafruit_BNO055 bno = Adafruit_BNO055(I2C_COMPASS_ADDRESS);
};

#endif