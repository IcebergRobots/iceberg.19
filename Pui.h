#ifndef Pui_h
#define Pui_h

#include "Core.h"

#define NUMBER_OF_KEYS 19

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
    KeyListener compassCalibration();
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
    void update();
  private:
    KeyListener k[NUMBER_OF_KEYS] = {
      KeyListener(PUI_POTI, 0, 500, 200), // decreasePage
      KeyListener(PUI_POTI, 0, 500, 200), // increasePage
      KeyListener(PUI_POTI, 0),           // selectPage
      KeyListener(PUI_POTI, 2000),        // resetProperties (left + right)
      KeyListener(PUI_ROT_BUTTON, 0),           // selectMenu
      KeyListener(PUI_POTI, 0, 1000, 0),  // kick
      KeyListener(PUI_POTI, 0, 0, 0),     // compass
      KeyListener(PUI_POTI, 0),           // animation
      KeyListener(PUI_POTI, 500),         // lineCalibration
      KeyListener(PUI_POTI, 500),         // lightBeamCalibration
      KeyListener(PUI_START, 0, 0, 0),       // start
      KeyListener(PUI_STOP, 0, 0, 0),        // stop
      KeyListener(PUI_POTI, 0, 0, 0),     // record (start + stop)
      KeyListener(PUI_POTI, 0),           // headstart (lever)
      KeyListener(PUI_POTI, 0),           // motor     (lever)
      KeyListener(PUI_POTI, 0),           // bluetooth (lever)
      KeyListener(PUI_POTI, 0),           // kicker    (lever)
      KeyListener(PUI_POTI, 0),           // bottom    (lever)
      KeyListener(PUI_POTI, 0),           // debug     (lever)
    };
};
#endif
