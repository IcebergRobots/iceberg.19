#ifndef Container_h
#define Container_h

#include "core.h"

#define INITIALISATION  0
#define UPDATE          1

class Container
{
  public:
    Container();
    //virtual void update() = 0;
    void linkNode(Container *container);
    void updateAll();
    

  private:
    void operation(byte id);
    void updateNode();
    Container *nextObject = NULL;
};

#endif