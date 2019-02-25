#include "Container.h"

/*********************************************************************
  Constructor
  add this object to the container
*********************************************************************/
Container::Container() {
    getObjects(this);
}

LinkedList<int> *Container::getObjects(Container *myself) {
    static LinkedList<int> objectAddresses;
    if (myself == NULL) return &objectAddresses;
    else objectAddresses.add((int)myself);
}