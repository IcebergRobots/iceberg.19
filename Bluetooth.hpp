#ifndef Bluetooth_hpp
#define Bluetooth_hpp

#include "Config.hpp"


class Bluetooth{
    public:
        Bluetooth();
        
        send(String function, String values[]);
        update();


    private:
        int _expectedbytes;
        byte buffer[6];
        bool processed;

        bool process(byte currentbyte);
        void extract();
        int processvalues(byte currentbyte);
        byte valuetobyte(int value);
        char functionbyte(String function, int value[]);
        byte checkbyte(int values[]);

};

#endif

