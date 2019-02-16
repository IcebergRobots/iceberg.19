#include "Container.h"

/*********************************************************************
  Constructor
  add this object to the container
*********************************************************************/
Container::Container() {
    operation(INITIALISATION);
}

void Container::linkNode(Container *container) {
    nextObject = container;
}

void Container::updateAll() {
    operation(UPDATE);
}

void Container::operation(byte id) {
    static Container *firstObject, *previousObject;   
    
    switch (id)
    {
        case INITIALISATION:
            if (previousObject != NULL) previousObject->linkNode(this);
            previousObject = this;
            if (firstObject != NULL) firstObject = this;
            break;

        case UPDATE:
            if (firstObject != NULL) firstObject->updateNode();
            break;

        default:
            break;
    }
}

void Container::updateNode() {
    if (nextObject != NULL) nextObject->updateNode();
}