class Partner{
    public:
        void setAnimation(bool state);
        void start();
        void stop();
        void setRoleStriker(bool striker);
        void move();
        void getPosition(int *x, int *y);
        int[2] getPosition();
        int getXPosition();
        int getYPosition();
        byte getRating();
        bool isActive();
    private:
        Value rating = Value();
        int xPosition;
        int yPosition;
        Timer heartPartner    = Timer(    500             );  // wurde Heartbeat des Gegners empfangen?

}