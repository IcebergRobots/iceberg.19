#ifndef Container_h
#define Container_h

#include "core.h"

#define DO_INITIALISATION  0
#define DO_UPDATE          1
#define DO_SET             2

class Container
{
  public:
    Container();
    static void updateAll();
    static void setAll();
    static void operation(byte id, Container *myself=NULL);

    void nextNode(byte id);
    void linkNode(Container *myself);

    void update();
    void set();

  private:
    Container *nextObject = NULL;
};

#endif