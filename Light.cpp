#include "Light.h"

/*****************************************************
  Constructor
*****************************************************/
Light::Light(int numPixels, Pin *pin) : Adafruit_NeoPixel(numPixels, pin->getPin(), NEO_GRB + NEO_KHZ800) {}


/*****************************************************
  Set all leds of the board
*****************************************************/
void Light::setAllColor(unsigned long color) {
  for (int i = 0; i < numPixels(); i++) {
    setPixelColor(i, color);
  }
  show();
}
void Light::setAllColor(byte red, byte green, byte blue) {
  setAllColor(Color(red, green, blue));
}

/*****************************************************
  Display a color wheel
  @param offset: rotation of the color wheel
*****************************************************/
void Light::setAllWheel(int offset) {
  for (int i = 0; i < numPixels(); i++) {
    setPixelColor(i, wheelToColor(offset + i * 256 / numPixels()));
  }
  board.show();
}

/*****************************************************
  Led zeigt rot, grün oder aus
  @param board: Light-Board
  @param pos: Nummer der Led im Board
  @param state: darzustellender Zustand
    0: rot/aus
    1: grün
    2: magenta
    3: rot
  @param (optional) hideRed: soll rot unsichtbar sein?
*****************************************************/
void Light::setPixelState(byte pos, byte state, bool hideRed) {
  switch (state) {
    default:  //case: 0
      // Information falsch (magenta)
      // hideRed=true Information nicht verfügbar (aus)
      // hideRed=true Information nicht relevant (aus)
      setPixelColor(pos, (!hideRed) * 150, 0, (!hideRed) * 150);
      break;
    case 1: 
      // Information wahr (grün)
      setPixelColor(pos, 0, 255, 0);
      break;
    case 2:
      // Wahrnung (blau)
      // Information ungewiss (blau)
      setPixelColor(pos, 0, 180, 120);
      break;
    case 3:
      // Kritische Warnung (magenta)
      // Information falsch (magenta)
      setPixelColor(pos, 255, 0, 150);
      break;
  }
}

/*****************************************************
  wandle Zustand in Farbe eines Farbkreises um
  @param board: Light-Board
  @param pos: [0 bis 255]
  0:    rot
  85:   grün
  170:  blau
  255:  rot
*****************************************************/
unsigned long Light::wheelToColor(byte pos) {
  if (pos < 85) { // rot bis grün
    return Color(255 - pos * 3, pos * 3, 0);
  } else if (pos < 170) { // grün bis blau
    pos -= 85;
    return Color(0, 255 - pos * 3, pos * 3);
  } else { // blau bis rot
    pos -= 170;
    return Color(pos * 3, 0, 255 - pos * 3);
  }
}

Light puiBoard = new Light(12,io.puiLight);