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
  headingPID.SetMode(AUTOMATIC);
  headingPID.SetOutputLimits(-255, 255);
  headingPID.SetSampleTime(10);

  trackingPID.SetMode(AUTOMATIC);
  trackingPID.SetOutputLimits(-120, 120);
  headingPID.SetSampleTime(10);
}

void Pilot::update()
{
  int direction = 0;
  int speed = 255;
  int faceDir = 0;

  headingPIDin = io.heading.get();
  trackingPIDin = io.ball.get();

  if(io.striker || true){  
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // STRIKER /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(io.seeBall.get()){
      direction = trackBall();
      speed = mapConstrain(io.ballWidth.get(), 5, 35, SPEED_BALL_FAR, SPEED_BALL);
      //speed = 50;

      if (direction > 60)
      {
        direction = 100;
        speed = SPEED_SIDEWAY;
      }
      else if (direction < -60)
      {
        direction = -100;
        speed = SPEED_SIDEWAY;
      }
    }
    else{
      speed = SPEED_BACKWARDS;
      direction = 180;
    }
    Serial.println("DIR: "+String(direction)+" PWR: "+String(speed));
    //drive(direction, speed, face(faceDir));
    drive(direction, speed, 0);
    execute();
  }
  else{
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // KEEPER
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  }
}

int Pilot::face(int angle)
{
  io.driveOrientation.set(angle);
  headingPIDtarget = io.driveOrientation.get();

  // Misst die Kompassabweichung vom Tor [-180 bis 179]
  headingPIDin = (double)io.heading.get();
  
  if (io.driveEnabled.on())
  {
    headingPID.Compute();
    return -headingPIDout; // [-255 bis 255]
  }
  else
    return 0;
}

int Pilot::trackBall()
{
  trackingPIDtarget = 0;
  trackingPID.Compute();
  
  return trackingPIDout;
}

void Pilot::computePIDs(){
  headingPID.Compute();
  trackingPID.Compute();
}

Pilot drive;