#include "IO.h"

/*********************************************************************
  Constructor
*********************************************************************/
IO::IO() {}

void IO::update() {
  if (DEBUG_LOOP) beginSegment("io");

  for(int i = 0; i < Value::getAll().size(); i++) {
    Value *v = Value::getAll().get(i);
    v->update();
  }

  if (DEBUG_LOOP) endSegment();
}

IO io;