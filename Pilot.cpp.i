#include "Pilot.h"

Pilot::Pilot() {
}

void Pilot::changeState() {
  // set state
  byte tempState = state;
  if (state >= 6) {
    // aktiv
    if (isKeeper() && !mate.timeout()) setState(0, "passive"); // werden passiv
    else if (io.seeBall.off()) setState(5, "blind"); // wir werden blind
  } else {
    // passiv
    if (io.seeBall.on() && io.state.is(BACK) && io.state.is(FREEING) && (isRusher() || mate.timeout())) setState(6, "active"); // wir werden aktiv
    // sehenBall &   keine Pfostendrehung   &  (Stürmer   oder  Singleplayer)
  }

io.state.set(BACK, "rearward>");

  switch (io.state.get()) {
    // Passivspiel
    case BACK: // Nach hinten
      if (us.back() <= COURT_REARWARD_MAX) setState(1, "rearward<");
      else if (millis() - stateTimer > BACKWARD_MAX_DURATION) setState(4, "time>");
      break;

    case 1: // Torverteidigung
      if (io.seeBall.off() && io.state.period() >= SIDEWARD_MAX_DURATION) {
        if (us.back() > COURT_REARWARD_MAX) setState(0, "rearward>"); // fahre rückwärts
        else if (io.striker.on()) setState(2, "time>,keeper");     // wechsle in Drehmodus
        else setDirection(TOGGLE, "time>,rusher");  // wechsle Fahrrichtung
      } else if (millis() - stateTimer > SIDEWARD_MIN_DURATION) {
        if (us.back() > COURT_REARWARD_MAX) setState(0, "rearward>"); // fahre rückwärts
        else if (millis() - lineTimer < 100) setDirection(TOGGLE, "line");
        else if (io.seeBall.on()) {
          if (io.ballLeft.on()) {
            setDirection(LEFT, "ball<");
            stateTimer += 200 - SIDEWARD_MIN_DURATION;
          } else if (io.ballRight.on()) {
            setDirection(RIGHT, "ball>");
            stateTimer += 200 - SIDEWARD_MIN_DURATION;
          }
        } else if (atGatepost() && isKeeper()) setState(2, "gatepost");  // wechsle in Drehmodus
      }
      break;

    case 2: // Pfostendrehung hin
      if (io.seeBall.on()) {
        if (stateLeft && io.ballRight.on()) setState(3, "ball>");
        else if (!stateLeft && io.ballLeft.on()) setState(3, "ball<");
      }
      else if (millis() - stateTimer > TURN_MAX_DURATION) setState(3, "time>");
      else if (stateLeft && heading < -ANGLE_TURN_MAX * 0.9) setState(3, "angle<");
      else if (!stateLeft && heading > ANGLE_TURN_MAX * 0.9) setState(3, "angle>");
      break;

    case 3: // Pfostendrehung zurück
      if (io.seeBall.on()) {
        if (stateLeft) {
          if ((ball / 3 + heading) > -ANGLE_RETURN_MIN) setDirection(TOGGLE, "ball|");
          else if (io.ballLeft.on()) setState(2, "ball<");
        } else {
          if ((ball / 3 + heading) < ANGLE_RETURN_MIN) setDirection(TOGGLE, "ball|");
          else if (io.ballRight.on()) setState(2, "ball>");
        }
      }
      else if (millis() - stateTimer > RETURN_MAX_DURATION) setDirection(TOGGLE, "time>");
      else if (abs(heading) < ANGLE_RETURN_MIN) setDirection(TOGGLE, "angle|");
      break;

    case 4: // Befreiung
      if (millis() - stateTimer > GOAL_STUCK_DURATION) setState(0, "time>"); // fahre wieder rückwärts und warte erneut * Sekunden
      break;

    case 5: // Seitlich verloren
      if (millis() - stateTimer > LOST_DURATION) setState(0, "time>");
      else if (io.ballRight.on() && stateLeft) setDirection(RIGHT, "ball>");
      else if (io.ballLeft.on() && !stateLeft) setDirection(LEFT, "ball<");
      break;


    // Aktivspiel
    case 6: // Ballverfolgung
      if (io.ballRight.on()) stateLeft = RIGHT;
      else if (io.ballLeft.on()) stateLeft = LEFT;

      if (closeBall && seeGoal) setState(7, "closeBall");
      break;

    case 7: // Torausrichtung
      if (!closeBall) setState(6, "farBall");
      else if (!seeGoal) setState(6, "!goal");
      else if (goal < -BALL_ANGLE_TRIGGER) stateLeft = LEFT;
      else if (goal > BALL_ANGLE_TRIGGER) stateLeft = RIGHT;
      else if (abs(ball) < BALL_ANGLE_TRIGGER) setState(8, "goal|");
      break;

    case 8: // Angriff
      if (io.ballRight.on()) stateLeft = RIGHT;
      else if (io.ballLeft.on()) stateLeft = LEFT;

      if (!closeBall) setState(6, "!closeBall");
      break;
  }
  if (tempState == 0 && state == 1) stateTimer = max(0, millis() - SIDEWARD_MIN_DURATION / 2);
  else if (tempState != state) stateTimer = millis();

  if (seeWest || seeEast) {
    int angle = 0;
    if (seeWest) angle += west;
    else angle += east - 30;
    if (seeEast) angle += east;
    else angle += west + 30;

    angle /= 2;
    if (sendAvoidTimer > 200)  ccLeft = angle < 0;
    else {
      if (angle > BALL_ANGLE_TRIGGER) ccLeft = RIGHT;
      else if (angle < -BALL_ANGLE_TRIGGER) ccLeft = LEFT;
    }

    if (state >= 6) {
      if (millis() - sendAvoidTimer > 100) {
        sendAvoidTimer = millis();
        byte data[1];
        if (ccLeft) data[0] = 'w';
        else data[0] = 'e';
        mate.send(data, 1); // avoid mate
      }
    }
  }
}

void Pilot::play() {
  changeState();

  switch (state) {
    case 0: // Nach hinten
      if (us.back() && us.back() < 80) {
        drivePower = SPEED_PENALTY;
        driveState = "v penalty";
      } else {
        drivePower = SPEED_BACKWARDS;
        driveState = "v backward";
      }
      // fahre rückwärts und lenke zur Mitte vor dem Tor
      if (us.left() && us.left() < COURT_BORDER_MIN) driveDirection = -constrain(map(COURT_BORDER_MIN - us.left(), 0, 30, 180, 180 - ANGLE_PASSIVE_MAX), 180 - ANGLE_PASSIVE_MAX, 180);
      else if (us.right() && us.right() < COURT_BORDER_MIN) driveDirection = constrain(map(COURT_BORDER_MIN - us.right(), 0, 30, 180, 180 - ANGLE_PASSIVE_MAX), 180 - ANGLE_PASSIVE_MAX, 180);
      else driveDirection = 180;

      driveRotation = ausrichten(0);
      drivePower = max(drivePower - abs(driveRotation), 0);
      m.drive(driveDirection, drivePower, driveRotation);
      break;

    case 1: // Torverteidigung
      // fahre seitlich vor dem Tor
      if (io.seeBall.on()) drivePower = map(abs(ball), 0, BALL_ANGLE_TRIGGER, SPEED_KEEPER, 0.6 * SPEED_KEEPER);
      else drivePower = SPEED_KEEPER;
      if (stateLeft) {
        driveDirection = ANGLE_SIDEWAY;
        driveState = "< sideward";
        if (us.left() < COURT_BORDER_MIN) drivePower = SPEED_KEEPER * 0.7; // fahre langsamer am Spielfeldrand
      } else {
        driveDirection = -ANGLE_SIDEWAY;
        driveState = "> sideward";
        if (us.right() < COURT_BORDER_MIN) drivePower = SPEED_KEEPER * 0.7; // fahre langsamer am Spielfeldrand
      }
      if (us.back() < COURT_REARWARD_MIN) driveDirection *= map(us.back(), 0, COURT_REARWARD_MIN, 8, 10) / 10.0; // fahre leicht schräg nach vorne

      driveRotation = ausrichten(0);
      drivePower = max(drivePower - abs(driveRotation), 0);
      m.drive(driveDirection, drivePower, driveRotation);
      break;

    case 2: // Pfostendrehung hin
      if (io.ballRight.on()) driveRotation = 160;
      if (stateLeft) {
        if (io.seeBall.on()) driveOrientation = constrain(ball / 3 + heading, -ANGLE_TURN_MAX, 0);
        else driveOrientation = -ANGLE_TURN_MAX;
        driveState = "< turn";
      } else {
        if (io.seeBall.on()) driveOrientation = constrain(ball / 3 + heading, 0, ANGLE_TURN_MAX);
        else driveOrientation = ANGLE_TURN_MAX;
        driveState = "> turn";
      }

      if (io.ballRight.on()) driveRotation = 0.9 * ausrichten(driveOrientation);
      else driveRotation = ausrichten(driveOrientation);
      m.drive(0, 0, driveRotation);
      break;

    case 3: // Pfostendrehung zurück
      if (stateLeft) {
        if (io.seeBall.on()) driveOrientation = constrain(ball / 3 + heading, -ANGLE_TURN_MAX, 0);
        else driveOrientation = 0;
        driveState = "< return";
      } else {
        if (io.seeBall.on()) driveOrientation = constrain(ball / 3 + heading, 0, ANGLE_TURN_MAX);
        else driveOrientation = 0;
        driveState = "> return";
      }

      if (io.ballRight.on()) driveRotation = 0.9 * ausrichten(driveOrientation);
      else driveRotation = ausrichten(driveOrientation);
      m.drive(0, 0, driveRotation);
      break;

    case 4: // Befreiung
      // fahre * Sekunden geradeaus, um nicht mehr am Tor hängenzubleiben
      driveState = "^ free";

      driveRotation = ausrichten(0);
      drivePower = max(SPEED_FREE - abs(driveRotation), 0);
      m.drive(0, drivePower, driveRotation);
      break;

    case 5: // Seitlich verloren
      // fahre * Sekunden zur Seite, um den Ball wiederzufinden
      if (stateLeft) {
        driveDirection = ANGLE_SIDEWAY;
        driveState = "< lost";
        if (us.left() < 60) drivePower *= 0.7;  // fahre langsamer am Spielfeldrand
      } else {
        driveDirection = -ANGLE_SIDEWAY;
        driveState = "> lost";
        if (us.right() < 60) drivePower *= 0.7; // fahre langsamer am Spielfeldrand
      }

      driveRotation = ausrichten(0);
      drivePower = max(SPEED_LOST - abs(driveRotation), 0);
      m.drive(driveDirection, drivePower, driveRotation);
      break;

    case 6: // Ballverfolgung
      if (io.seeBall.off()) rotMulti = ROTATION_SIDEWAY;
      else if (ballWidth > 100) rotMulti = ROTATION_TOUCH;
      else if (ballWidth > 40) rotMulti = ROTATION_10CM;
      else if (ballWidth > 20) rotMulti = ROTATION_18CM;
      else rotMulti = ROTATION_AWAY;

      drivePower = map(constrain(ballWidth, 5, 35), 5, 35, SPEED_BALL_FAR, SPEED_BALL);
      driveDirection = map(ball, -X_CENTER, X_CENTER, (float)rotMulti, -(float)rotMulti);
      if (driveDirection > 60) {
        // seitwärts bewegen, um Torsusrichtung aufrecht zu erhalten
        driveState = "> follow";
        driveDirection = 100;
        drivePower = SPEED_SIDEWAY;
      } else if (driveDirection < -60) {
        // seitwärts bewegen, um Torsusrichtung aufrecht zu erhalten
        driveState = "< follow";
        driveDirection = -100;
        drivePower = SPEED_SIDEWAY;
      } else {
        driveState = "^ follow";

        driveRotation = ausrichten(0);
        drivePower = max(drivePower - abs(driveRotation), 0);
        m.drive(driveDirection, drivePower, driveRotation);
      }

      if (hasBall && !seeGoal) kick();
      break;

    case 7: // Torausrichtung
      // orientiere dich zum Ball
      // bringe Ball und Tor in eine Linie
      if (!stateLeft) {
        // Tor ist links
        driveDirection = ANGLE_GOAL;
        driveState = "< close";
      } else {
        // Tor ist rechts
        driveDirection = -ANGLE_GOAL;
        driveState = "> close";
      }
      driveOrientation = constrain(ball / 3 + heading, -ANGLE_GOAL_MAX, ANGLE_GOAL_MAX);

      if (millis() - stateTimer < 200) m.brake(true); // bremse kurz ab
      else {
        driveRotation = ausrichten(driveOrientation);
        drivePower = max(SPEED_CLOSE - abs(driveRotation), 0);
        m.drive(driveDirection, drivePower, driveRotation);
      }
      break;

    case 8: // Angriff
      if (io.seeBall.on()) driveDirection = constrain(map(ball, -X_CENTER, X_CENTER, 50, -50), -50, 50);
      else driveDirection = 0;
      driveState = "^ attack";
      if (hasBall) kick();

      driveRotation = ausrichten(driveOrientation);           // übernehme den letzten Kompasswinkel
      drivePower = max(SPEED_ATTACK - abs(driveRotation), 0);
      m.drive(driveDirection, drivePower, driveRotation);
      break;
  }
}

void Pilot::setState(byte s, String reason) {
  if (s != state) {
    if (DEBUG_STATE) debug(String(state) + "->" + String(s) + ":" + reason);
    state = s;
    stateTimer = millis();
  }
}

void Pilot::setDirection(byte dir, String reason) {
  if (dir > 1) dir = !stateLeft;
  if (dir != stateLeft) {
    stateLeft = dir;
    if (DEBUG_STATE && stateLeft)  debug(String(state) + "<:" + reason);
    if (DEBUG_STATE && !stateLeft) debug(String(state) + ">:" + reason);
    stateTimer = millis();
    setState(1, "toggle");
  }
}

void Pilot::setRusher(bool force) {
  if (isKeeper()) {
    if (force || millis() - roleTimer > ROLE_COOLDOWN) {
      role = 1;
      roleTimer = millis();
      ledTimer = millis() - 101;
    }
  }
}

void Pilot::setKeeper(bool force) {
  if (isRusher()) {
    if (force || millis() - roleTimer > ROLE_COOLDOWN) {
      role = 0;
      roleTimer = millis();
      ledTimer = millis() - 101;
    }
  }
}

bool Pilot::isRusher() {
  return role;
}

bool Pilot::isKeeper() {
  return !role;
}

unsigned long Pilot::lastRoleToggle() {
  return millis() - roleTimer;
}

byte Pilot::getState() {
  return state;
}

bool Pilot::atGatepost() {
  //if (true || isPenaltyFree) {
  // benutze Abstand in Bewegungsrichtung
  if (stateLeft) return us.left() < COURT_BORDER_MIN;
  else           return us.right() < COURT_BORDER_MIN;
  /*} else {
    // benutze Abstand gegen Bewegungsrichtung
    if (stateLeft) return us.right() > COURT_POST_TO_BORDER;
    else           return us.left() > COURT_POST_TO_BORDER;
    }*/
}

Pilot pilot();