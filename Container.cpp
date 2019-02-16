#include "Container.h"

/*********************************************************************
  Constructor
  add this object to the container
*********************************************************************/
Container::Container() {
    operation(INITIALISATION, this);
}

void Container::linkNode(Container *container) {
    nextObject = container;
}

void Container::updateAll() {
    operation(UPDATE, NULL);
}

void Container::operation(byte id, Container *myself) {
    static Container *firstObject, *previousObject;   
    
    switch (id)
    {
        case INITIALISATION:
            if (previousObject != NULL) previousObject->linkNode(myself);
            previousObject = myself;
            if (firstObject != NULL) firstObject = myself;
            break;

        case UPDATE:
            if (firstObject != NULL) firstObject->updateNode();
            break;

        default:
            break;
    }
}

void Container::updateNode() {
    update();
    if (nextObject != NULL) nextObject->updateNode();
}