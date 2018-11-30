#ifndef Pui_h
#define Pui_h

#include "Core.h"

#define NUMBER_OF_KEYS 20

class Pui
{
  public:
    Pui();
    KeyListener decreasePage();
    KeyListener increasePage();
    KeyListener selectPage();
    KeyListener resetProperties();
    KeyListener selectMenu();
    KeyListener kick();
    KeyListener compass();
    KeyListener animation();
    KeyListener lineCalibration();
    KeyListener lightBeamCalibration();
    KeyListener start();
    KeyListener stop();
    KeyListener record();
    KeyListener headstart();
    KeyListener motor();
    KeyListener bluetooth();
    KeyListener kicker();
    KeyListener bottom();
    KeyListener debug();
    KeyListener silent();
    void update();
  private:
    KeyListener k[20] = {
      KeyListener(PUI_ROT_BTN, 0, 500, 200), // decreasePage
      KeyListener(PUI_ROT_BTN, 0, 500, 200), // increasePage
      KeyListener(PUI_ROT_BTN, 0),           // selectPage
      KeyListener(PUI_ROT_BTN, 2000),        // resetProperties (left + right)
      KeyListener(PUI_ROT_BTN, 0),           // selectMenu
      KeyListener(PUI_ROT_BTN, 0, 1000, 0),  // kick
      KeyListener(PUI_ROT_BTN, 0, 0, 0),     // compass
      KeyListener(PUI_ROT_BTN, 0),           // animation
      KeyListener(PUI_ROT_BTN, 500),         // lineCalibration
      KeyListener(PUI_ROT_BTN, 500),         // lightBeamCalibration
      KeyListener(PUI_START, 0, 0, 0),       // start
      KeyListener(PUI_STOP, 0, 0, 0),        // stop
      KeyListener(PUI_ROT_BTN, 0, 0, 0),     // record (start + stop)
      KeyListener(PUI_ROT_BTN, 0),           // headstart (lever)
      KeyListener(PUI_ROT_BTN, 0),           // motor     (lever)
      KeyListener(PUI_ROT_BTN, 0),           // bluetooth (lever)
      KeyListener(PUI_ROT_BTN, 0),           // kicker    (lever)
      KeyListener(PUI_ROT_BTN, 0),           // bottom    (lever)
      KeyListener(PUI_ROT_BTN, 0),           // debug     (lever)
      KeyListener(PUI_ROT_BTN, 0)            // silent    (lever)
    };
};
#endif
