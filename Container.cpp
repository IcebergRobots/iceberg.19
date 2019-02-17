#include "Container.h"

/*********************************************************************
  Constructor
  add this object to the container
*********************************************************************/
Container::Container() {
    operation(DO_INITIALISATION, this);
}

void Container::updateAll() {
    operation(DO_UPDATE);
}

void Container::setAll() {
    operation(DO_SET);
}

void Container::operation(byte id, Container *myself) {
    static Container *firstObject    = NULL;
    static Container *previousObject = NULL;
    
    switch (id)
    {
        case DO_INITIALISATION:
            if (myself != NULL) {
                if (previousObject != NULL) previousObject->linkNode(myself);
                previousObject = myself;
                if (firstObject == NULL) firstObject = myself;
            }
            break;

        case DO_UPDATE:
        case DO_SET:
            if (firstObject != NULL) firstObject->nextNode(id); 
            break;

        default:
            break;
    }
}

void Container::nextNode(byte id) {
    switch (id)
    {
        case DO_UPDATE:
            update();
            break;
    
        case DO_SET:
            set();
            break;

        default:
            break;
    }
    if (nextObject != NULL) nextObject->nextNode(id);
}

void Container::linkNode(Container *myself) {
    nextObject = myself;
}

void Container::update() {}
void Container::set() {}