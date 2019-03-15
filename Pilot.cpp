#include "Pilot.h"

/*********************************************************************
  Konstruktor
  - konfiguriere die Motor-Pins
  - konfiguriere PID-Regler
*********************************************************************/
Pilot::Pilot()
{
  setAxisAngle(70);
  m[0].setPins(&io.m0Current, &io.m0Dir1, &io.m0Dir2, &io.m0Speed);
  m[1].setPins(&io.m1Current, &io.m1Dir1, &io.m1Dir2, &io.m1Speed);
  m[2].setPins(&io.m2Current, &io.m2Dir1, &io.m2Dir2, &io.m2Speed);
  m[3].setPins(&io.m3Current, &io.m3Dir1, &io.m3Dir2, &io.m3Speed);

  // konfiguriere PID-Regler
  myPID.SetTunings(PID_FILTER_P, PID_FILTER_I, PID_FILTER_D);
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255, 255);
}

/*****************************************************
  aktualisiere die Zustandsmaschine
  - prüfe ob Zustandsänderungen sinnvoll sind
*****************************************************/
void Pilot::setState()
{
  if (io.seeBall.change() && io.seeBall.on()) // finden wir den Ball gerade wieder?
    io.state.set(BALL_TRACKING, "view");
  if (io.seeBall.change() && io.seeBall.off()) // verlieren wir den Ball gerade?
    io.state.set(BACK, "blind");

  switch (io.state.get()) // durchlaufe die Zustandsmaschine
  {
  default:
  case BACK:  // fahre nach hinten
    if (us.back() <= COURT_REARWARD_MAX) // sind wir schon im Strafraum?
      io.state.set(GOALKEEPER, "enter penalty area");
    //else if (io.state.outsidePeriod(BACKWARD_MAX_DURATION)) io.state.set(FREEING, "time>");
    break;
  case GOALKEEPER:
    if (io.seeBall.off() && io.stateDirection.outsidePeriod(SIDEWARD_MAX_DURATION)) // fahren wir schon zu lange blind in eine Richtung?
      io.stateDirection.set(io.stateDirection.off(), "turn:timeout"); // ändere die Richtung wegen Zeitüberschreitung
    else if (io.seeBall.on() || io.stateDirection.outsidePeriod(SIDEWARD_MIN_DURATION)) // verhindere zu häufige Richtungswechsel außer bei Ballsicht
    {
      // positioniere dich vor den Ball
      if (io.seeBallLeft.on())
        io.stateDirection.set(LEFT, "turn:ball left");
      else if (io.seeBallRight.on())
        io.stateDirection.set(RIGHT, "turn:ball right");

      if (us.back() > COURT_REARWARD_MAX) // haben wir den Strafraum verlassen
        io.state.set(BACK, "leave penalty area"); // fahre wieder nach hinten
      else if (atGatepost())  // sind wir ausreichend 
        io.stateDirection.set(io.stateDirection.off(), "turn:at gatepost");
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

void Pilot::update()
{
  if (DEBUG_LOOP)
    beginSegment(F("m"));

  setState();

  if (io.driveEnabled.falling())
    brake();

  int direction = 0;
  int speed = 255;
  int rotation = 0;
  int rotMulti = 40;

  switch (io.state.get())
  {
  default:
  case BACK:
    if (false /*us.back() && us.back() < 80*/)
    {
      speed = SPEED_PENALTY;
      //driveState = "v penalty";
    }
    else
    {
      speed = SPEED_BACKWARDS;
      //driveState = "v backward";
    }
    // fahre rückwärts und lenke zur Mitte vor dem Tor
    /*if (us.left() && us.left() < COURT_BORDER_MIN) direction = -constrain(map(COURT_BORDER_MIN - us.left(), 0, 30, 180, 180 - ANGLE_PASSIVE_MAX), 180 - ANGLE_PASSIVE_MAX, 180);
      else if (us.right() && us.right() < COURT_BORDER_MIN) direction = constrain(map(COURT_BORDER_MIN - us.right(), 0, 30, 180, 180 - ANGLE_PASSIVE_MAX), 180 - ANGLE_PASSIVE_MAX, 180);
      else*/
    direction = 180;

    drive(180, speed, face(0));
    break;
  case GOALKEEPER:
    if (io.seeBall.off())
      speed = map(abs(io.ball.get()), 0, X_CENTER, SPEED_KEEPER, 0.6 * SPEED_KEEPER);
    else
      speed = SPEED_KEEPER;
    if (io.stateDirection.left())
    {
      direction = ANGLE_SIDEWAY;
      if (us.left() < COURT_BORDER_MIN)
        speed = SPEED_KEEPER * 0.7; // fahre langsamer am Spielfeldrand
    }
    else
    {
      direction = -ANGLE_SIDEWAY;
      if (us.right() < COURT_BORDER_MIN)
        speed = SPEED_KEEPER * 0.7; // fahre langsamer am Spielfeldrand
    }
    if (us.back() < COURT_REARWARD_MIN)
      direction *= map(us.back(), 0, COURT_REARWARD_MIN, 8, 10) / 10.0; // fahre leicht schräg nach vorne

    drive(direction, speed, face(0));
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
    if (io.seeBall.off())
      rotMulti = ROTATION_SIDEWAY;
    else if (io.ballWidth.get() > 100)
      rotMulti = ROTATION_TOUCH;
    else if (io.ballWidth.get() > 40)
      rotMulti = ROTATION_10CM;
    else if (io.ballWidth.get() > 20)
      rotMulti = ROTATION_18CM;
    else
      rotMulti = ROTATION_AWAY;

    speed = mapConstrain(io.ballWidth.get(), 5, 35, SPEED_BALL_FAR, SPEED_BALL);
    direction = map(io.ball.get(), -X_CENTER, X_CENTER, (float)rotMulti, -(float)rotMulti);
    if (direction > 60)
    {
      // seitwärts bewegen, um Torsusrichtung aufrecht zu erhalten
      //driveState = "> follow";
      direction = 100;
      speed = SPEED_SIDEWAY;
    }
    else if (direction < -60)
    {
      // seitwärts bewegen, um Torsusrichtung aufrecht zu erhalten
      //driveState = "< follow";
      direction = -100;
      speed = SPEED_SIDEWAY;
    }
    else
    {
      //driveState = "^ follow";
    }
    drive(direction, speed, face(0));
    break;
  case GOAL_AIMING:

    break;
  case ATTACK:

    break;
  case DODGE:

    break;
  }
  if (DEBUG_LOOP)
    endSegment();
}

void Pilot::steer(int angle)
{
  io.driveAngle.set(angle);
}
void Pilot::accelerate(int speed)
{
  io.drivePower.set(speed);
}
int Pilot::face(int angle, int speed)
{
  //angle = circulate(angle, -179,  180);
  io.driveOrientation.set(angle);
  pidSetpoint = io.driveOrientation.get();
  // Misst die Kompassabweichung vom Tor [-180 bis 179]
  pidIn = (double)io.heading.get();
  if (io.driveEnabled.on())
  {
    myPID.Compute();
    return -pidOut; // [-255 bis 255]
  }
  else
    return 0;
}

bool Pilot::atGatepost()
{
  // benutze Abstand in Bewegungsrichtung
  if (io.stateDirection.left())
    return io.farSidelineLeft.on();
  else
    return io.farSidelineRight.on();
}

Pilot drive;