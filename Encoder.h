#ifndef Encoder_h
#define Encoder_h

#define ENCODER1_ID 8         // Encoder an den Motoren 0 und 3
#define ENCODER2_ID 9         // Encoder an den Motoren 1 und 2
#define MAXTIME 20

class Encoder {
    public: 
        Encoder();
        
        void update();
        int getSpeed(int id);

    private:
        int _encNr;
        int _dataNr;
        int speed[4];
        unsigned long timer = 0;
};

#endif