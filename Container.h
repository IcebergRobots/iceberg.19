#ifndef Container_h
#define Container_h

#include "core.h"

#define INITIALISATION  0
#define UPDATE          1

class Container
{
  public:
    Container();
    void updateAll();
    //virtual void update() = 0;
    void linkNode(Container *container);

  private:
    void container(byte operation);
    Container *nextObject = NULL;
};

#endif