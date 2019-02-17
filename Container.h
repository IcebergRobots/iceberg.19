#ifndef Container_h
#define Container_h

#include "core.h"

template <typename T> int objects() {
  LinkedList<int> *objects = T::getObjects();
  return objects->size();
}
template <typename T> int objects(int i) {
  LinkedList<int> *objects = T::getObjects();
  return objects->get(i);
}

class Container
{
  public:
    Container();
    static LinkedList<int> *getObjects(Container *myself=NULL);
    
  private:
};

#endif