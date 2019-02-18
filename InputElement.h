#ifndef InputElement_h
#define InputElement_h

#include "Container.h"

class InputElement : public Container
{
public:
    InputElement());
    virtual void update() = 0;
private:
};

#endif