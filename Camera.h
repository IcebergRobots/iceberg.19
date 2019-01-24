#ifndef PixyCam_h
#define PixyCam_h

#include "IO.h"
#include "Demand.h"
#include <SPI.h>
#include <Pixy.h>

#define BUFFER_SIZE 128

class Camera : private Pixy, public Demand
{
  public:
    Camera();
    void init();
    void frame();
    
  private:
    byte blockCount = 0;    // Anzahl der gesehenen Blöcke
    byte blockCountBall = 0;// Anzahl der Ball Blöcke
    byte blockCountGoal = 0;// Anzahl der Tor Blöcke
};
extern Camera camera;

#endif
