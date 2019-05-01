#ifndef Encoder_h
#define Encoder_h

class Encoder {
    public: 
        Encoder(int encNr, int dataNr);
        
        void update();
        int getSpeed();

    private:
        int _encNr;
        int _dataNr;
        int speed;
        unsigned long timer = 0;
        int maxtime = 20;

};

#endif