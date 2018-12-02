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
    Key(int8_t _pin, uint32_t _preDelay);
    Key(int8_t _pin, uint32_t _preDelay, uint32_t _postDelay, uint32_t _repititionDelay);
    bool stroke();
    bool permanent();
    bool click();
    void update();
  private:
    void cooldown(uint32_t delay);
    int8_t pin = 0;
    bool active = false;
    uint32_t clicks = 0;
    uint32_t preDelay = 0;
    uint32_t postDelay = -1;        // infinity
    uint32_t repititionDelay = -1;  // infinity
    uint32_t cooldownTimer = 0;
};
#endif