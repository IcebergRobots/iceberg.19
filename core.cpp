#include "core.h"

/*****************************************************
  sende Text zum PC
*****************************************************/
void debugln(long num, bool space) {   debugln(String(num)); }
void debugln(String str, bool space) { debug(str + "\n");    }
void debug(long num, bool space) {     debug(String(num), space);   }
void debug(String str, bool space) {
  if (DEBUG && io.turbo.off()) {
    if (io.hasDebugHead.on() && space) str = " " + str;
    if (io.hasDebugHead.off()) {
      io.hasDebugHead.set(true);
      str = "\n" + format("t" + io.runtime.str(), 6) + " " + str;
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

String format(String str, unsigned int minLength, unsigned int maxLength) {
  byte l = str.length();
  for(int i = 0; l + i < minLength; i++) {
    str = " " + str;
  }
  if (maxLength + 1 != 0) return str.substring(str.length()-maxLength,str.length());
  else return str;
}
String format(long num, unsigned int minLength, unsigned int maxLength, bool sign) {
  String str = String(num);
  if(sign && num >= 0) str = "+" + str;
  return format(str, minLength, maxLength);
}

void beginSegment(String name) {
  if(io.runtime.period() + 1 == 0 || DEBUG_SEGMENT) { // if in setup or DEBUG_SEGMENT
    debug(name + "{");
    io.segment.set();
  }
}
void endSegment() {
  if(io.runtime.period() + 1 == 0 || DEBUG_SEGMENT) debug("}"+ io.segment.str(), false); // if in setup or DEBUG_SEGMENT
}