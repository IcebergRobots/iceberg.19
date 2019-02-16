#ifndef Container_h
#define Container_h

#include "core.h"

#define INITIALISATION  0
#define UPDATE          1

class Container
{
  public:
    Container();
    void linkNode(Container *container);
    static void updateAll();

    virtual void update() = 0;

  private:
    static void operation(byte id, Container *myself);
    void updateNode();
    Container *nextObject = NULL;
};

#endif