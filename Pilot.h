#ifndef Pilot_h
#define Pilot_h

#include "Chassis.h"
#include <PID_v1.h>
#include "Ultrasonic.h"

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

  bool atGatepost();

  int face(int angle = 0);
  int trackBall();

private:
  // WICHTUNG DER PID-REGLER
  double pidSetpoint; // Nulllevel [-180 bis 180] Winkel des Tours
  double pidIn;       // Kompasswert [-180 bis 180]
  double pidOut;      // Rotationsstärke [-255 bis 255]

  // Regler Roboterausrichtung
  double headingPIDin = 0; // Kompasswinkel als Eingabe [-179 bis 180]
  double headingPIDout = 0; // Rotationsstärke als Ausgabe [-255 bis 255]
  double headingPIDtarget = 0;  // Sollwert der Ausrichtung [-179 bis 180]
  PID headingPID = PID (&headingPIDin, &headingPIDout, &headingPIDtarget, HEADING_PID_P, HEADING_PID_I, HEADING_PID_D, DIRECT);

  // Regler Ballverfolgung
  double trackingPIDin = 0; // Ballwinkel als Eingabe []
  double trackingPIDout = 0;
  double trackingPIDtarget = 0;
  PID trackingPID = PID(&trackingPIDin, &trackingPIDout, &trackingPIDtarget, 0, 0, 0, DIRECT);
};
extern Pilot drive;

#endif
