#include "IO.h"

/*********************************************************************
  Constructor
*********************************************************************/
IO::IO() {}

void IO::update() {
  if (DEBUG_LOOP) beginSegment("io");

  debug(objects<Value>());

  for(int i = 0; i < objects<Value>(); i++) {
    debug(i, false);
    Value *v = objects<Value>(i);
    v->update();
  }
  /*
  for(int i = 0; i < objects<Timer>(); i++) {
    Timer *t = objects<Timer>(i);
    t->update();
  }

  for(int i = 0; i < objects<Pin>(); i++) {
    Pin *p = objects<Pin>(i);
    p->update();
  }

  for(int i = 0; i < objects<Key>(); i++) {
    Key *k = objects<Key>(i);
    k->update();
  }
  
  for(int i = 0; i < objects<Shortcut>(); i++) {
    Shortcut *s = objects<Shortcut>(i);
    s->update();
  }
  */

  if (DEBUG_LOOP) endSegment();
}

IO io;