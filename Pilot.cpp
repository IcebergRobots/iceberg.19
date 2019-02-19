#include "Pilot.h"

/*********************************************************************
  Constructor
  - configurate chassis
*********************************************************************/
Pilot::Pilot() {
  setAxisAngle(70);
  m[0].setPins(&io.m0Current, &io.m0Dir1, &io.m0Dir2, &io.m0Speed);
  m[1].setPins(&io.m1Current, &io.m1Dir1, &io.m1Dir2, &io.m1Speed);
  m[2].setPins(&io.m2Current, &io.m2Dir1, &io.m2Dir2, &io.m2Speed);
  m[3].setPins(&io.m3Current, &io.m3Dir1, &io.m3Dir2, &io.m3Speed);
}

void Pilot::prepare() {
  if (io.seeBall.rising()) io.state.set(BALL_TRACKING, "view");
  if (io.seeBall.falling()) io.state.set(BACK, "blind");
}

void Pilot::update() {
  int direction = 0;
  int speed = 255;
  int rotation = 0;
  int rotMulti = 40;

  switch (io.state.get()) {
    default:
    case BACK:
      if (false /*us.back() && us.back() < 80*/) {
        speed = SPEED_PENALTY;
        //driveState = "v penalty";
      } else {
        speed = SPEED_BACKWARDS;
        //driveState = "v backward";
      }
      // fahre rückwärts und lenke zur Mitte vor dem Tor
      /*if (us.left() && us.left() < COURT_BORDER_MIN) direction = -constrain(map(COURT_BORDER_MIN - us.left(), 0, 30, 180, 180 - ANGLE_PASSIVE_MAX), 180 - ANGLE_PASSIVE_MAX, 180);
      else if (us.right() && us.right() < COURT_BORDER_MIN) direction = constrain(map(COURT_BORDER_MIN - us.right(), 0, 30, 180, 180 - ANGLE_PASSIVE_MAX), 180 - ANGLE_PASSIVE_MAX, 180);
      else*/ direction = 180;

      rotation = 0 //ausrichten(0);
      speed = max(speed - abs(rotation), 0);
      m.drive(direction, speed, rotation);
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
      speed = map(constrain(ballWidth, 5, 35), 5, 35, SPEED_BALL_FAR, SPEED_BALL);
      direction = map(ball, -X_CENTER, X_CENTER, (float)rotMulti, -(float)rotMulti);
      if (direction > 60) {
        // seitwärts bewegen, um Torsusrichtung aufrecht zu erhalten
        //driveState = "> follow";
        direction = 100;
        speed = SPEED_SIDEWAY;
      } else if (direction < -60) {
        // seitwärts bewegen, um Torsusrichtung aufrecht zu erhalten
        //driveState = "< follow";
        direction = -100;
        speed = SPEED_SIDEWAY;
      } else {
        //driveState = "^ follow";

        rotation = 0; //ausrichten(0);
        speed = max(speed - abs(rotation), 0);
        m.drive(direction, speed, rotation);
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