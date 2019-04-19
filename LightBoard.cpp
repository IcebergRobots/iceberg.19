#include "LightBoard.h"

/*****************************************************
  Constructor
*****************************************************/
LightBoard::LightBoard(int numPixels, int pin, unsigned long lockedPeriod = 0, unsigned long cooldownPeriod = 0)
{
  numLEDs = numPixels;
  this->addressOffset = startingIndexCounter;
  FastLED.addLeds<WS2812B, pin>(ledStrips, startingIndexCounter, numPixels);

  setCooldown(cooldownPeriod);
  setLocked(lockedPeriod);

  startingIndexCounter += numPixels;;
}

/*****************************************************
  Set all leds of the board
*****************************************************/
void LightBoard::setAllColor(unsigned long color)
{
  for (int i = 0; i < numPixels(); i++)
    setPixelColor(i, color);
}
void LightBoard::setAllColor(byte red, byte green, byte blue)
{
  setAllColor(Color(red, green, blue));
}

/*****************************************************
  Display a color wheel
  @param offset: rotation of the color wheel
*****************************************************/
void LightBoard::setAllWheel(int offset)
{
  for (int i = 0; i < numPixels(); i++)
    setPixelColor(i, wheelToColor(offset + i * 256 / numPixels()));
}

/*****************************************************
  Led zeigt rot, grün oder aus
  @param pos: Nummer der Led im Board
  @param state: darzustellender Zustand

  @param (optional) hideRed: soll rot unsichtbar sein?
*****************************************************/
void LightBoard::setPixelState(byte pos, byte state)
{
  switch (state)
  {
  default:
  case STATE_DEFAULT:
    setPixelColor(pos, 0, 0, 0); // aus
    break;
  case STATE_ACTIVE:
    setPixelColor(pos, 0, 255, 0); // grün
    break;
  case STATE_OK:
    setPixelColor(pos, 0, 0, 255); // blau
    break;
  case STATE_WARNING:
    setPixelColor(pos, 255, 69, 0); // orange
    break;
  case STATE_ERROR:
    setPixelColor(pos, 255, 0, 0); // rot
    break;
  }
}

/*****************************************************
  wandle Zustand in Farbe eines Farbkreises um
  @param pos: [0 bis 255]
  0:    rot
  85:   grün
  170:  blau
  255:  rot
*****************************************************/
unsigned long LightBoard::wheelToColor(byte pos)
{
  if (pos < 85)
  { // rot bis grün
    return Color(255 - pos * 3, pos * 3, 0);
  }
  else if (pos < 170)
  { // grün bis blau
    pos -= 85;
    return Color(0, 255 - pos * 3, pos * 3);
  }
  else
  { // blau bis rot
    pos -= 170;
    return Color(pos * 3, 0, 255 - pos * 3);
  }
}

bool LightBoard::isEnabled()
{
  return LIGHT_ENABLED && io.battery.on();
}

void LightBoard::setPixelColor(byte pos, byte _r, byte _g, byte _b){
  ledStrips[this->addressOffset+pos] = CRGB(_r*brightness/255,_g*brightness/255,_b*brightness/255);
}

void LightBoard::show(){
  FastLED.show()
}

void LightBoard::setBrightness(byte b){
  brightness = b;
}

byte LightBoard::numPixels(){
  return numLEDs;
}
