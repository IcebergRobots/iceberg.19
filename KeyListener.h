#ifndef KeyListener_h
#define KeyListener_h

#include "Config.h"

/***********************************************************
                                  click
                 ┌─────────┬────────┴──────┬───────────────┬─╌                                                
              stroke   permanent       permanent       permanent    
      on╔════════╪═════════╪═══════════════╪═══════════════╪═════ ... ═╗
Button  ║        ┊         ┊               ┊               ┊           ║
     off║        ┊         ┊               ┊               ┊           ║
════════╝        ┊postDelay┊               ┊               ┊           ╚══════                
        ┊preDelay┊         ┊repititionDelay┊repititionDelay┊                                             

************************************************************/

class KeyListener
{
  public:
    KeyListener(int8_t _pin);
    KeyListener(int8_t _pin, unsigned long _preDelay);
    KeyListener(int8_t _pin, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay);
    bool stroke();
    bool permanent();
    bool click();
    void update();
  private:
    int8_t pin = 0;
    bool active = false;
    unsigned long clicks = 0;
    unsigned long preDelay = 0;
    unsigned long postDelay = -1;
    unsigned long repititionDelay = -1;
    unsigned long cooldownTimer = 0;
};
#endif