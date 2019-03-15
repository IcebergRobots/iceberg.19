#ifndef Container_h
#define Container_h

#include "core.h"

/*********************************************************************
  gib die Anzahl an Objekten dieser Klasse zurück
*********************************************************************/
template <typename T> extern int objects() {
  LinkedList<int> *objects = T::getObjects();
  return objects->size();
}

/*********************************************************************
  wähle ein Objekt des Containers
  @param i: Index des Objektes in der Liste
  - gibt einen Pointer (konvertiert als Integer) zum Objekt zurück
*********************************************************************/
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