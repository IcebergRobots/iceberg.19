#include "core.h"

/*****************************************************
  ist der Wert endlich also nicht unendlich?
  @param value: Zahlenwert
*****************************************************/
bool isFinite(unsigned long value)
{
  return value + 1 != 0;
}
bool isFinite(unsigned int value)
{
  return value + 1 != 0;
}
bool isFinite(byte value)
{
  return value + 1 != 0;
}

/*****************************************************
  moduliere den Wert in ein Intervall
  @param value: Zahlenwert
  @param min: untere Intervallgrenze
  @param max: obere Intervallgrenze
*****************************************************/
int circulate(int value, int min, int max)
{
  max = max(min, max - min + 1);
  value -= min;
  value %= max;
  if (value < 0)
    value += max;
  value += min;
  return value;
}

int pinMode(byte pin)
{
  byte bit = digitalPinToBitMask(pin);
  byte port = digitalPinToPort(pin);
  volatile byte *reg = portModeRegister(port);
  if (*reg & bit)
    return (OUTPUT);

  volatile byte *out = portOutputRegister(port);
  return ((*out & bit) ? INPUT_PULLUP : INPUT);
}


/*****************************************************
  starte den Arduino neu
  - setze den Befehlszähler auf 0
*****************************************************/
void reset()
{
  asm("jmp 0"); // starte den Arduino neu
}

/*****************************************************
  schneide eine Zahl oder Text auf eine bestimmte Länge
  @param str: Text
  @param num: Zahl
  @param minLength: Mindestlänge der Ausgabe
  @param max: obere Maximallänge der Ausgabe
*****************************************************/
String format(String str, unsigned int minLength, unsigned int maxLength)
{
  byte l = str.length();
  for (int i = 0; l + i < minLength; i++)
  {
    str = " " + str;
  }
  if (maxLength + 1 != 0)
    return str.substring(str.length() - maxLength, str.length());
  else
    return str;
}
String format(long num, unsigned int minLength, unsigned int maxLength, bool sign)
{
  String str = String(num);
  if (sign && num >= 0)
    str = "+" + str;
  return format(str, minLength, maxLength);
}

bool blink(unsigned long period, float proportion) {
  return (millis() % period) <= proportion * period;
}

long mapConstrain(long x, long in_min, long in_max, long out_min, long out_max) {
  x = constrain(x, in_min, in_max);
  return map(x, in_min, in_max, out_min, out_max);
}

void beginSegment(String name) { beginSegmentFunction(name); }
void endSegment() { endSegmentFunction(); }
void (*beginSegmentFunction)(String);
void (*endSegmentFunction)();