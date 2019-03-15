#ifndef Line_h
#define Line_h

#include "IO.h"
#include "Pilot.h"

class Line
{
public:
    Line();
    void update();
 private:
    void extendAvoid();
    void fetch();
};

extern bool isLineFetchRequest;
extern Line line;

#endif