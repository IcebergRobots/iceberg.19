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
  myPID.SetTunings(PID_FILTER_P, PID_FILTER_I, PID_FILTER_D);
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255);
}

void Pilot::setState() {
  if (io.seeBall.change() && io.seeBall.on()) io.state.set(BALL_TRACKING, "view");
  if (io.seeBall.change() && io.seeBall.off()) io.state.set(BACK, "blind");

  switch (io.state.get()) {
    default:
    case BACK:
      if (us.back() <= COURT_REARWARD_MAX) io.state.set(GOALKEEPER, "dis_b<");
      //else if (io.state.outsidePeriod(BACKWARD_MAX_DURATION)) io.state.set(FREEING, "time>");
      break;
    case GOALKEEPER:
      if (io.seeBall.off() && io.stateDirection.outsidePeriod(SIDEWARD_MAX_DURATION)) io.stateDirection.set(io.stateDirection.off(), "t>");
      else if (io.seeBall.on() || io.stateDirection.outsidePeriod(SIDEWARD_MIN_DURATION)) {
        if      (io.seeBallLeft.on())  io.stateDirection.set(LEFT, "ball<");
        else if (io.seeBallRight.on()) io.stateDirection.set(RIGHT, "ball>");

        if (us.back() > COURT_REARWARD_MAX) io.state.set(BACK, "dis_b>"); // fahre rückwärts
        if (atGatepost()) io.stateDirection.set(io.stateDirection.off(), "g");
      }
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

void Pilot::update() {
  if (DEBUG_LOOP) beginSegment(F("m"));

  setState();

  if (io.driveEnabled.falling()) {
    disable();
  }

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

      rotation = face(0);
      speed = max(speed - abs(rotation), 0);
      drive(180, speed, rotation);
      break;
    case GOALKEEPER:
      if (io.seeBall.off()) speed = map(abs(io.ball.get()), 0, BALL_CENTER_TOLERANCE, SPEED_KEEPER, 0.6 * SPEED_KEEPER);
        else speed = SPEED_KEEPER;
        if (io.stateDirection.left()) {
          direction = ANGLE_SIDEWAY;
          if (us.left() < COURT_BORDER_MIN) speed = SPEED_KEEPER * 0.7; // fahre langsamer am Spielfeldrand
        } else {
          direction = -ANGLE_SIDEWAY;
          if (us.right() < COURT_BORDER_MIN) speed = SPEED_KEEPER * 0.7; // fahre langsamer am Spielfeldrand
        }
        if (us.back() < COURT_REARWARD_MIN) direction *= map(us.back(), 0, COURT_REARWARD_MIN, 8, 10) / 10.0; // fahre leicht schräg nach vorne

        rotation = face(0);
        speed = max(speed - abs(rotation), 0);
        drive(direction, speed, rotation);
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
      if (io.seeBall.off()) rotMulti = ROTATION_SIDEWAY;
      else if (io.ballWidth.get() > 100) rotMulti = ROTATION_TOUCH;
      else if (io.ballWidth.get() > 40) rotMulti = ROTATION_10CM;
      else if (io.ballWidth.get() > 20) rotMulti = ROTATION_18CM;
      else rotMulti = ROTATION_AWAY;

      speed = mapConstrain(io.ballWidth.get(), 5, 35, SPEED_BALL_FAR, SPEED_BALL);
      direction = map(io.ball.get(), -X_CENTER, X_CENTER, (float)rotMulti, -(float)rotMulti);
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
      }
        rotation = face(0);
        speed = max(speed - abs(rotation), 0);
        drive(direction, speed, rotation);
      break;
    case GOAL_AIMING:

      break;
    case ATTACK:

      break;
    case DODGE:

      break;
  }
  if (DEBUG_LOOP) endSegment();
}


void Pilot::steer(int angle) {
  io.driveAngle.set(angle);
}
void Pilot::accelerate(int speed) {
  io.drivePower.set(speed);
}
int Pilot::face(int angle, int speed) {
  io.driveOrientation.set(angle);
  pidSetpoint = io.driveOrientation.get();
  // Misst die Kompassabweichung vom Tor [-180 bis 179]
  pidIn = (double) io.heading.get();
  if (io.driveEnabled.on()) {
    myPID.Compute();
    return -pidOut; // [-255 bis 255]
  }
  else return 0;
}

bool Pilot::atGatepost() {
  // benutze Abstand in Bewegungsrichtung
  if (io.stateDirection.left()) return us.left() < COURT_BORDER_MIN;
  else                          return us.right() < COURT_BORDER_MIN;
}

Pilot drive;