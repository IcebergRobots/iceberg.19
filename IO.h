#ifndef IO_h
#define IO_h

#include "Core.h"

class IO
{
public:
  IO();
  Key decreasePage = Key(PUI_POTI, 0, 500, 200);   // decreasePage
  Key increasePage = Key(PUI_POTI, 0, 500, 200);   // increasePage
  Key selectPage = Key(PUI_POTI, 0);               // selectPage
  Key resetProperties = Key(PUI_POTI, 2000);       // resetProperties (left + right)
  Key selectMenu = Key(PUI_ROT_BUTTON, 0, 1000);   // selectMenu
  Key kick = Key(PUI_POTI, 0, 1000, 0);            // kick
  Key compassCalibration = Key(PUI_POTI, 0, 0, 0); // compassCalibration
  Key animation = Key(PUI_POTI, 0);                // animation
  Key lineCalibration = Key(PUI_POTI, 500);        // lineCalibration
  Key lightBeamCalibration = Key(PUI_POTI, 500);   // lightBeamCalibration
  Key start = Key(PUI_START, 0);                   // start
  Key stop = Key(PUI_STOP, 0);                     // stop
  Key record = Key(PUI_POTI, 0, 0, 0);             // record (start + stop)
  Key headstart = Key(PUI_POTI, 0);                // headstart (lever)
  Key motor = Key(PUI_POTI, 0);                    // motor     (lever)
  Key bluetooth = Key(PUI_POTI, 0);                // bluetooth (lever)
  Key kicker = Key(PUI_POTI, 0);                   // kicker    (lever)
  Key bottom = Key(PUI_POTI, 0);                   // bottom    (lever)
  Key debug = Key(PUI_POTI, 0);                    // debug     (lever)
  void update();

private:

};
#endif
