#ifndef Container_h
#define Container_h

class Container
{
  public:
    Container();
    static void updateAll();
    void update() = 0;

  private:
    void container();
};

#endif