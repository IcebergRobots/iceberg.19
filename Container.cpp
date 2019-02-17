#include "Container.h"

/*********************************************************************
  Constructor
  add this object to the container
*********************************************************************/
Container::Container() {
    getAll(this);
}

LinkedList<int> Container::getAll(Container *myself) {
    static LinkedList<int> objectAddresses;
    if (myself == NULL) return objectAddresses;
    else objectAddresses.add((int)myself);
}