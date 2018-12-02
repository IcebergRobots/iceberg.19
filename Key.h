#ifndef Key_h
#define Key_h

#include "Core.h"

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

class Key
{
  public:
    Key(int8_t _pin);
    Key(int8_t _pin, uint64_t _preDelay);
    Key(int8_t _pin, uint64_t _preDelay, uint64_t _postDelay, uint64_t _repititionDelay);
    bool stroke();
    bool permanent();
    bool click();
    void update();
  private:
    void cooldown(uint64_t delay);
    int8_t pin = 0;
    bool active = false;
    uint64_t clicks = 0;
    uint64_t preDelay = 0;
    uint64_t postDelay = -1;        // infinity
    uint64_t repititionDelay = -1;  // infinity
    uint64_t cooldownTimer = 0;
};
#endif