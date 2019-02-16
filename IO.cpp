#include "IO.h"

/*********************************************************************
  Constructor
*********************************************************************/
IO::IO() {}

void IO::update() {
  if (DEBUG_LOOP) beginSegment("io");
  Value::updateAll();
  if (DEBUG_LOOP) endSegment();
}

IO io;