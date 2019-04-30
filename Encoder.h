#ifndef Encoder_h
#define Encoder_h

class Encoder {
    public: 
        Encoder(int nr);
        
        void update();
        int getSpeed();
        int getPwr(int pwr, int motor);

    private:
        int encNr;
        int dataNr;
        int speed;

};

#endif