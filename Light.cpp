#include "Light.h"

/*****************************************************
  Konstruktor
*****************************************************/
Light::Light() {
  setCooldown(10);
}

void Light::light() {
  beginSegment("l:s");
  setBoard(puiBoard, 255);
  puiBoard.setBrightness(map(io.puiPoti.get(), 0, 1023, 0, 255));
  io.indHearbeat.set(map(abs(int(millis() % 500) - 250),0,250,-100,356));
  /*showState(puiBoard, 0, io.start.get());
  showState(puiBoard, 1, io.stop.get());
  showState(puiBoard, 2, io.record.get());
  showState(puiBoard, 3, io.start.stroke());
  showState(puiBoard, 4, io.stop.stroke());
  showState(puiBoard, 5, io.record.stroke());*/
  endSegment();

  beginSegment("l:e");
  puiBoard.show();
  endSegment();
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
void Light::showState(Adafruit_NeoPixel & board, byte pos, byte state, bool hideRed) {
  switch (state) {
    default:  //case: 0
      // Information falsch (magenta)
      // hideRed=true Information nicht verfügbar (aus)
      // hideRed=true Information nicht relevant (aus)
      board.setPixelColor(pos, (!hideRed) * 150, 0, (!hideRed) * 150);
      break;
    case 1: 
      // Information wahr (grün)
      board.setPixelColor(pos, 0, 255, 0);
      break;
    case 2:
      // Wahrnung (blau)
      // Information ungewiss (blau)
      board.setPixelColor(pos, 0, 180, 120);
      break;
    case 3:
      // Kritische Warnung (magenta)
      // Information falsch (magenta)
      board.setPixelColor(pos, 255, 0, 150);

      break;
  }
}

/*****************************************************
  Zeige Farbkreislauf auf Board
  @param board: Light-Board
  @param offset: Drehung des Farbkreises
*****************************************************/
void Light::wheelBoard(Adafruit_NeoPixel & board, int offset) {
  for (uint16_t i = 0; i < board.numPixels(); i++) {
    board.setPixelColor(i, wheelToColor(board, offset + i * 256 / board.numPixels()));
  }
  board.show();
}

/*****************************************************
  Schalte ein Board aus
  @param board: Light-Board
*****************************************************/
void Light::setBoard(Adafruit_NeoPixel & board, uint32_t color) {
  for (uint16_t i = 0; i < board.numPixels(); i++) {
    board.setPixelColor(i, color);
  }
  board.show();
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
uint32_t Light::wheelToColor(Adafruit_NeoPixel & board, byte pos) {
  if (pos < 85) {
    // rot bis grün
    return board.Color(255 - pos * 3, pos * 3, 0);
  } else if (pos < 170) {
    // grün bis blau
    pos -= 85;
    return board.Color(0, 255 - pos * 3, pos * 3);
  } else {
    // blau bis rot
    pos -= 170;
    return board.Color(pos * 3, 0, 255 - pos * 3);
  }
}

Light light = Light();