#include "Utility.h"

void reset() {
  asm ("jmp 0");   // starte den Arduino neu
}

int shift(int &value, int min, int max) {
  max -= min;
  value = (max + (value - min % max)) % max + min; // wandle Drehposition in Zustand von 0 bis ROTARY_RANGE um
  return value;
}

/*****************************************************
  Berechne alle Statuswerte und Zustände
*****************************************************/
void calculateStates() {
}


/*****************************************************
  sende Text zum PC
*****************************************************/
void debug(String str) {
  if (DEBUG && !silent) {
    if (!hasDebugHead) {
      hasDebugHead = true;
      str = "\n" + String(millis())+ str;
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

void prepareDebug() {
  hasDebugHead = false;
  if (DEBUG_LOOP) debug();
}
