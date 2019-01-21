#ifndef PixyCam_h
#define PixyCam_h

#include "core.h"

#define BUFFER_SIZE 128

class PixyCam : private Pixy, public Demand
{
  public:
    PixyCam();
    void init();
    void frame();
    
  private:
    byte blockCount = 0;    // Anzahl der gesehenen Blöcke
    byte blockCountBall = 0;// Anzahl der Ball Blöcke
    byte blockCountGoal = 0;// Anzahl der Tor Blöcke
};
extern PixyCam camera;

#endif
