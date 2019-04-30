#include "Led.h"

// Implementierung: OBJEKTE
extern Display d;
extern Player p;
extern Led led;
extern Mate mate;
extern Pilot m;
extern Ultrasonic us;
extern Adafruit_NeoPixel bottom;
extern Adafruit_NeoPixel info;
extern Input input;

Led::Led() {}

void Led::heartbeat(){
  #define HEARTBEAT_LOOPTIME 500
  int i = map(millis() % HEARTBEAT_LOOPTIME*2,0,HEARTBEAT_LOOPTIME,0,255);
  analogWrite(HEARTBEAT_LED, i>255 ? i : 255-i);
}

/*****************************************************
  Aktualisiere alle Leds bzw. zeige die Animation
*****************************************************/
void Led::led() {
  //TODO
  if (!timer) {
    // setze Helligkeit zurück
    bottom.setBrightness(BOTTOM_BRIGHTNESS);
    info.setBrightness(INFO_BRIGHTNESS);

    // setze Boden-Leds
    if (!input.switch_bodensensor || isLifted) setBoard(bottom, BOTTOM_LENGTH, bottom.Color(0, 0, 0));
    else setBoard(bottom, BOTTOM_LENGTH, bottom.Color(255, 255, 255));

    info.show();
  } else {
    // maximale Helligkeit
    bottom.setBrightness(255);
    info.setBrightness(255);
    byte angle = (int)((millis() - timer) * 0.2) % 256;
    wheelBoard(bottom, BOTTOM_LENGTH, angle);
    wheelBoard(info, INFO_LENGTH, angle);
  }
  ledTimer = millis();
}

/*****************************************************
  Lege Leds auf Statusinformation fest
*****************************************************/
void Led::set() {
  //TODO
  showState(info, 0,  0                                                           );  //PARTY
  showState(info, 1,  batState * (batState != 3 || millis() % 250 < 125), true    );  //Voltage
  showState(info, 2,  0                                                           );  //ColCode
  showState(info, 3,  seeGoal                                                     );  //Goal
  showState(info, 4,  seeBall                                                     );  //Ball
  showState(info, 5,  isLifted * 3                                      , true    );  //Lifted
  showState(info, 6,  !silent                                                     );  //Debug
  showState(info, 7,  input.switch_bodensensor                                    );  //Bodensensor
  showState(info, 8,  input.switch_kick                                           );  //Kicker
  showState(info, 9,  input.switch_bluetooth                                      );  //Bluetooth
  showState(info, 10, m.getMotEn() + (!m.getMotEn()&&input.switch_motor)*2        );  //Motors
  showState(info, 11, input.switch_headstart                                      );  //Headstart
  /*
  // zeige Statuswerte an
  showState(info, 0, stateFine);
  showState(info, 1, batState * (batState != 3 || millis() % 250 < 125), true);
  showState(info, 2, millis() % 1000 < 200, true);

  showState(matrix, 0, input.switch_kick);
  showState(matrix, 1, !input.switch_motor);
  showState(matrix, 2, seeBall + closeBall, true);
  showState(matrix, 3, hasBall, true);
  showState(matrix, 4, !mate.timeout());
  //showState(matrix, 5, Bodensensor verfügbar);
  showState(matrix, 6, isLifted * 3, true);
  showState(matrix, 7, pixyState, true);
  showState(matrix, 8, !onLine);
  showState(matrix, 9, seeGoal, true);
  //showState(matrix, 10, !us.timeout() * (2 - us.check()));
  if (p.isKeeper()) showState(matrix, 11, 1, true);
  else if (p.isRusher()) showState(matrix, 11, 3, true);
  else showState(matrix, 11, 0, true);
  }*/
}

/*****************************************************
  Starte die Animation
*****************************************************/
void Led::start() {
  if (ANIMATION) timer = millis();
}

/*****************************************************
  Beende die Animation
*****************************************************/
void Led::cancel() {
  if (timer) {
    timer = 0;
    led();
  }
}

/*****************************************************
  Läuft die Animation gerade?
*****************************************************/
bool Led::isAnimation() {
  return timer;
}

unsigned long Led::lastAnimation() {
  return millis() - timer;
}

/*****************************************************
  Led zeigt rot, grün oder aus
  @param board: Led-Board
  @param pos: Nummer der Led im Board
  @param (optional) state: darzustellender Zustand
  0: rot/aus
  1: grün
  2: gelb
  3: rot
  @param hideRed: soll rot unsichtbar sein?
*****************************************************/
void Led::showState(Adafruit_NeoPixel & board, byte pos, byte state, bool hideRed) {
  switch (state) {
    default:  //case: 0
      /*
         Information falsch (magenta)
         hideRed=true Information nicht verfügbar (aus)
         hideRed=true Information nicht relevant (aus)
      */
      board.setPixelColor(pos, (!hideRed) * 255, 0, 0);
      break;
    case 1:
      /*
         Information wahr (grün)
      */
      board.setPixelColor(pos, 0, 255, 0);
      break;
    case 2:
      /*
         Wahrnung (blau)
         Information ungewiss (blau)
      */
      board.setPixelColor(pos, 140, 127, 0);
      break;
    case 3:
      /*
         Kritische Warnung (magenta)
         Information falsch (magenta)
      */
      board.setPixelColor(pos, 255, 0, 0);

      break;
  }
}
void Led::showState(Adafruit_NeoPixel & board, byte pos, byte state) {
  showState(board, pos, state, false);
}

/*****************************************************
  Zeige Farbkreislauf auf Board
  @param board: Led-Board
  @param boardLength: Leds im Board
  @param offset: Drehung des Farbkreises
*****************************************************/
void Led::wheelBoard(Adafruit_NeoPixel & board, int boardLength, int offset) {
  for (int i = 0; i < boardLength; i++) {
    board.setPixelColor(i, wheelToColor(board, offset + i * 256 / boardLength));
  }
  board.show();
}

/*****************************************************
  Schalte ein Board aus
  @param board: Led-Board
  @param boardLength: Leds im Board
*****************************************************/
void Led::setBoard(Adafruit_NeoPixel & board, int boardLength, uint32_t color) {
  for (int i = 0; i < boardLength; i++) {
    board.setPixelColor(i, color);
  }
  board.show();
}

/*****************************************************
  wandle Zustand in Farbe eines Farbkreises um
  @param board: Led-Board
  @param pos: [0 bis 255]
  0:    rot
  85:   grün
  170:  blau
  255:  rot
*****************************************************/
uint32_t Led::wheelToColor(Adafruit_NeoPixel & board, byte pos) {
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

void Led::hymne() {
  // maximale Helligkeit
  // TODO bottom.setBrightness(255);
  // TODO matrix.setBrightness(255);
  // TODO info.setBrightness(255);
  // TODO setBoard(bottom, BOTTOM_LENGTH, bottom.Color(255, 255, 255));
  // TODO setBoard(matrix, MATRIX_LENGTH, matrix.Color(255, 255, 255));
  // TODO setBoard(info, INFO_LENGTH, info.Color(255, 255, 255));
  while (input.button_animation) {}
  // TODO setBoard(bottom, BOTTOM_LENGTH, 0);
  // TODO setBoard(matrix, MATRIX_LENGTH, 0);
  // TODO setBoard(info, INFO_LENGTH, 0);

  myTone(391, 586.956375, 652174);
  myTone(440, 195.652125, 217391);
  myTone(493, 391.30425, 434783);
  myTone(440, 391.30425, 434783);
  myTone(523, 391.30425, 434783);
  myTone(493, 391.30425, 434783);
  myTone(440, 195.652125, 217391);
  myTone(369, 195.652125, 217391);
  myTone(391, 391.30425, 434783);
  myTone(659, 391.30425, 434783);
  myTone(587, 391.30425, 434783);
  myTone(523, 391.30425, 434783);
  myTone(493, 391.30425, 434783);
  myTone(440, 391.30425, 434783);
  myTone(493, 195.652125, 217391);
  myTone(391, 195.652125, 217391);
  myTone(587, 782.6085, 869565);
  myTone(440, 391.30425, 434783);
  myTone(493, 391.30425, 434783);
  myTone(440, 195.652125, 217391);
  myTone(369, 195.652125, 217391);
  myTone(293, 391.30425, 434783);
  myTone(523, 391.30425, 434783);
  myTone(493, 391.30425, 434783);
  myTone(440, 195.652125, 217391);
  myTone(369, 195.652125, 217391);
  myTone(293, 391.30425, 434783);
  myTone(587, 391.30425, 434783);
  myTone(523, 391.30425, 434783);
  myTone(493, 586.956375, 652174);
  myTone(493, 195.652125, 217391);
  myTone(554, 391.30425, 434783);
  myTone(554, 195.652125, 217391);
  myTone(587, 195.652125, 217391);
  myTone(587, 782.6085, 869565);
  myTone(783, 586.956375, 652174);
  myTone(739, 195.652125, 217391);
  myTone(739, 195.652125, 217391);
  myTone(659, 195.652125, 217391);
  myTone(587, 391.30425, 434783);
  myTone(659, 586.956375, 652174);
  myTone(587, 195.652125, 217391);
  myTone(587, 195.652125, 217391);
  myTone(523, 195.652125, 217391);
  myTone(493, 391.30425, 434783);
  myTone(440, 586.956375, 652173);
  myTone(493, 97.8260625, 108696);
  myTone(523, 97.8260625, 108696);
  myTone(587, 195.652125, 217391);
  myTone(659, 195.652125, 217391);
  myTone(523, 195.652125, 217391);
  myTone(440, 195.652125, 217391);
  myTone(391, 391.30425, 434783);
  myTone(493, 195.652125, 217391);
  myTone(440, 195.652125, 217391);
  myTone(391, 782.6085, 869565);

}

void Led::myTone(unsigned int frequency, unsigned long duration, unsigned long pause) {
  if (timer) {
    if (input.button_encoder || !input.switch_debug) {
      cancel();
      return;
    }

    tone(BUZZER, frequency, duration);
    unsigned long timestamp = micros();
    while (micros() - timestamp < pause) {
      if (input.button_encoder || !input.switch_debug) {
        cancel();
        return;
      }
    }
  }
}

