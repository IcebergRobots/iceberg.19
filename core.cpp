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
      str = "\nt" + String(millis() - lastLoop) + " " + str;
      lastLoop = millis();
    }
    DEBUG_SERIAL.print(str);
  }
}

int shift(int &value, int min, int max) {
  max -= min;
  value = (max + (value - min % max)) % max + min; // wandle Drehposition in Zustand von 0 bis ROTARY_RANGE um
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
    lastSegment = millis();
  }
}
void endSegment() {
  if(DEBUG_SEGMENT) debug("}"+ String(millis() - lastSegment), false);
}