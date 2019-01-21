#include "core.h"

/*****************************************************
  sende Text zum PC
*****************************************************/
void debugln(long num, bool space) {   debugln(String(num)); }
void debugln(String str, bool space) { debug(str + "\n");    }
void debug(long num, bool space) {     debug(String(num), space);   }
void debug(String str, bool space) {
  if (DEBUG && !silent) {
    if (hasDebugHead && space) str = " " + str;
    if (!hasDebugHead) {
      hasDebugHead = true;
      str = "\nt" + String(io.runtime.since()) + " " + str;
      io.runtime.set();
    }
    DEBUG_SERIAL.print(str);
  }
}

int circulate(int value, int min, int max) {
  max = max(min, max - min + 1);
  value -= min;
  value %= max;
  if (value < 0) value += max;
  value += min;
  return value;
}

int pinMode(byte pin) {
  if (pin >= NUM_DIGITAL_PINS) return (-1);

  byte bit = digitalPinToBitMask(pin);
  byte port = digitalPinToPort(pin);
  volatile byte *reg = portModeRegister(port);
  if (*reg & bit) return (OUTPUT);

  volatile byte *out = portOutputRegister(port);
  return ((*out & bit) ? INPUT_PULLUP : INPUT);
}

void reset() {
  asm ("jmp 0");   // starte den Arduino neu
}

String format(String str, byte length) {
  byte l = str.length();
  for(int i = 0; l + i < length; i++) {
    str = " " + str;
  }
  return str.substring(l-length,l);
}
String format(long num, byte length, bool sign) {
  String str = String(num);
  if(sign && num >= 0) str = "+" + str;
  return format(str, length);
}



void beginSegment(String name) {
  if(DEBUG_SEGMENT) {
    debug(name + "{");
    io.segment.set();
  }
}
void endSegment() {
  if(DEBUG_SEGMENT) debug("}"+ String(io.segment.since()), false);
}