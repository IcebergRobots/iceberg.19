#include "Container.h"

/*********************************************************************
  Constructor
  add this object to the container
*********************************************************************/
Container::Container() {
    container(INITIALISATION);
}

void Container::updateAll() {
    container(UPDATE);
}

void Container::container(byte operation) {
    /*static LinkedList<Container> objects;
    
    switch (operation)
    {
        case INITIALISATION:
            objects.add(this);
            break;

        case UPDATE:
            for(int i = 0; i < objects.size(); i++) {
                objects.get(i)->update();
            }
            break;

        default:
            break;
    }*/
}