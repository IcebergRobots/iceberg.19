#include "IO.h"

/*********************************************************************
  Constructor
*********************************************************************/
IO::IO() {}

void IO::update() {
  if (DEBUG_LOOP) beginSegment("io");

  for(int i = 0; i < objects<Value>(); i++) {
    Value *v = objects<Value>(i);
    v->update();
  }

  if (DEBUG_LOOP) endSegment();
}

IO io;