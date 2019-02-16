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

void Container::linkNode(Container *container) {
    nextObject = container;
}

void Container::container(byte operation) {
    static Container *previousObject;   
    
    previousObject->linkNode(this);
    previousObject = this;
}