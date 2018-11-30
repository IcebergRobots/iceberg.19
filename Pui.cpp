#include "Pui.h"

/*********************************************************************
- Konstruktor
*********************************************************************/
Pui::Pui() {}

KeyListener Pui::decreasePage()         { return k[0];  }
KeyListener Pui::increasePage()         { return k[1];  }
KeyListener Pui::selectPage()           { return k[2];  }
KeyListener Pui::resetProperties()      { return k[3];  }
KeyListener Pui::selectMenu()           { return k[4];  }
KeyListener Pui::kick()                 { return k[5];  }
KeyListener Pui::compass()              { return k[6];  }
KeyListener Pui::animation()            { return k[7];  }
KeyListener Pui::lineCalibration()      { return k[8];  }
KeyListener Pui::lightBeamCalibration() { return k[9];  }
KeyListener Pui::start()                { return k[10]; }
KeyListener Pui::stop()                 { return k[11]; }
KeyListener Pui::record()               { return k[12]; }
KeyListener Pui::headstart()            { return k[13]; }
KeyListener Pui::motor()                { return k[14]; }
KeyListener Pui::bluetooth()            { return k[15]; }
KeyListener Pui::kicker()               { return k[16]; }
KeyListener Pui::bottom()               { return k[17]; }
KeyListener Pui::debug()                { return k[18]; }
KeyListener Pui::silent()               { return k[19]; }

void Pui::update() {
    for(int i = 0; i < NUMBER_OF_KEYS; i++) k[i].update();
}