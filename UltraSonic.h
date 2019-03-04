#ifndef UltraSonic_h
#define UltraSonic_h


class UltraSonic
{
    public:
    void update();
    void get(int usWanted);

    private:
    int us[5];
};

extern UltraSonic us;

#endif