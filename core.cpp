#include "core.h"

/*****************************************************
  sende eine Zahl mit Zeilenumbruch per USB an den PC
  @param num: Darzustellende Zahl
  @param space: Soll ein Leerzeichen an den Anfang der Nachricht angefügt werden?
*****************************************************/
void debugln(long num, bool space) { debugln(String(num)); }

/*****************************************************
  sende einen Text mit Zeilenumbruch per USB an den PC
  @param str: Darzustellender Text
  @param space: Soll ein Leerzeichen an den Anfang der Nachricht angefügt werden?
*****************************************************/
void debugln(String str, bool space) { debug(str + "\n"); }

/*****************************************************
  sende eine Zahl per USB an den PC
  @param num: Darzustellende Zahl
  @param space: Soll ein Leerzeichen an den Anfang der Nachricht angefügt werden?
*****************************************************/
void debug(long num, bool space) { debug(String(num), space); }

/*****************************************************
  sende einen Text per USB an den PC
  @param str: Darzustellender Text
  @param space: Soll ein Leerzeichen an den Anfang der Nachricht angefügt werden?
*****************************************************/
void debug(String str, bool space) { debugFunction(str, space); }

/*****************************************************
  Pointer zur richtigen Darstellungsmethode des Debuggings
  - Methode benutzt io Objekt, welches hier noch nicht verfügbar ist
  - dient zum nachträglichen Einfügen des Codes
*****************************************************/
void (*debugFunction)(String, bool);

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