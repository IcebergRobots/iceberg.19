#ifndef PixyCam_h
#define PixyCam_h

#include "IO.h"
#include "Demand.h"
#include <SPI.h>
#include <Pixy.h>

#define BUFFER_SIZE 128

class Camera : private Pixy
{
  public:
    Camera();
    void init();
    void update();

    tObject getBall();
    tObject getGoal();
    int getGoalPos();
    
  private:
    byte nrBlocks;
    int ballX;
    int ballY;
    int ballSize;
};

struct tObject {
  int x;
  int y;
  int width;
  int height;
}

#endif
