#ifndef Pui_h
#define Pui_h

#include "Core.h"

#define NUMBER_OF_KEYS 3

class Pui
{
  public:
    Pui();
    /*KeyListener start();
    KeyListener stop();
    KeyListener selectMenu();
    void update();*/
  private:
    KeyListener k = KeyListener(PUI_START, 0, 0, 0);    // flat

    /*
    KeyListener k[3] = {
      KeyListener(PUI_STOP, 0, 500, 200), // decreasePage
      KeyListener(PUI_STOP, 0, 500, 200), // increasePage
      KeyListener(PUI_STOP, 0),    // selectPage
      KeyListener(PUI_STOP, 2000),    // resetProperties (left + right)
      KeyListener(PUI_STOP, 0),    // selectMenu
      KeyListener(PUI_STOP, 0, 1000, 0),    // kick
      KeyListener(PUI_STOP, 0, 0, 0),    // compass
      KeyListener(PUI_STOP, 0),    // animation
      KeyListener(PUI_STOP, 500),    // lineCalibration
      KeyListener(PUI_STOP, 500),    // lightBeamCalibration
      KeyListener(PUI_STOP, 0),    // headstart
      KeyListener(PUI_STOP, 0),    // motor
      KeyListener(PUI_STOP, 0),    // bluetooth
      KeyListener(PUI_STOP, 0),    // kicker
      KeyListener(PUI_STOP, 0),    // bottom
      KeyListener(PUI_STOP, 0),    // debug
      KeyListener(PUI_STOP, 0),    // silent
      KeyListener(PUI_STOP, 600, 0, 0),    // flat
      KeyListener(PUI_START, 0, 0, 0),    // flat
      KeyListener(PUI_STOP, 0, 0, 0),    // flat
      KeyListener(PUI_ROT_BTN, 500, 2000, 100)    // flat
    };
    */
};
#endif
