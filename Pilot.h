#ifndef Pilot_h
#define Pilot_h

#include "Chassis.h"
#include <PID_v1.h>

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

  void setState();
  void update();

  void steer(int angle = 0);
  void accelerate(int speed = 255);
  int face(int angle = 0, int speed = 255);

private:
  // WICHTUNG DER PID-REGLER
  double pidSetpoint; // Nulllevel [-180 bis 180] Winkel des Tours
  double pidIn;       // Kompasswert [-180 bis 180]
  double pidOut;      // Rotationsstärke [-255 bis 255]
  PID myPID = PID(&pidIn, &pidOut, &pidSetpoint, PID_FILTER_P, PID_FILTER_I, PID_FILTER_D, DIRECT);
};
extern Pilot drive;

#endif
