#include "Pilot.h"

/*********************************************************************
  Constructor
  - configurate chassis
*********************************************************************/
Pilot::Pilot() : Chassis() {
  setAxisAngle(70);
  frontLeft.setPins (&io.m0Current, &io.m0Dir1, &io.m0Dir2, &io.m0Speed);
  frontRight.setPins(&io.m3Current, &io.m3Dir1, &io.m3Dir2, &io.m3Speed);
  backLeft.setPins  (&io.m1Current, &io.m1Dir1, &io.m1Dir2, &io.m1Speed);
  backRight.setPins (&io.m2Current, &io.m2Dir1, &io.m2Dir2, &io.m2Speed);
}

void Pilot::update() {
  switch (io.state.get()) {
    default:
    case BACK:

      break;
    case GOALKEEPER:

      break;
    case GOALPOST_GO:

      break;
    case GOALPOST_RETURN:

      break;
    case FREEING:

      break;
    case LOST:

      break;

    case BALL_TRACKING:

      break;
    case GOAL_AIMING:

      break;
    case ATTACK:

      break;
    case DODGE:

      break;
  }
}


void Pilot::steer(int angle) {
  io.driveAngle.set(angle);
}
void Pilot::accelerate(int speed) {
  io.drivePower.set(speed);
}
void Pilot::face(int angle, int speed) {
  
}

Pilot drive;