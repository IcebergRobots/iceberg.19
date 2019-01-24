#ifndef Pilot_h
#define Pilot_h

#include "IO.h"
#include "core.h"

#define BACK 0
#define GOALKEEPER 1
#define GOALPOST_GO 2
#define GOALPOST_RETURN 3
#define FREEING 4
#define LOST 5

#define BALL_TRACKING 6
#define GOAL_AIMING 7
#define ATTACK 8
#define DODGE 9

class Pilot : public Chassis
{

  public:
    Pilot();

    void update();
    
    void steer(int angle=0);
    void accelerate(int speed=255);
    void face(int angle=0, int speed=255);

  private:
  
};
extern Pilot drive;

#endif
