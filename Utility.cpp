#include "Utility.h"

/*****************************************************
  sende Text zum PC
*****************************************************/
void debug(String str) {
  if (DEBUG && !silent) {
    if (!hasDebugHead) {
      hasDebugHead = true;
      debug(millis());
    }
    DEBUG_SERIAL.print(str + " ");
  }
}
void debug(long num) {
  debug(String(num));
}
void debug() {
  debug("");
}

/*****************************************************
  sende Text zum PC
*****************************************************/
void debugln(String str) {
  debug(str + "\n");
}
void debugln(long num) {
  debugln(String(num));
}
void debugln() {
  debugln("");
}
