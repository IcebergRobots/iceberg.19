#include "Camera.h"

/*********************************************************************
  Constructor
*********************************************************************/
Camera::Camera(){}

/*********************************************************************
  initialisiert die SPI Kommunikation
*********************************************************************/
void Camera::init(){

}

void Camera::update(){
  nrBlocks = getBlocks();
  int blockCountBall = 0;
  int blockCountGoal = 0;

  for (byte i = 0; i < nrBlocks; i++)
    {                                      // geht alle erkannten Bloecke durch
      int height = blocks[i].height;       // Blockhöhe
      int width = blocks[i].width;         // Blockbreite
      int x = blocks[i].x - X_CENTER;      // Horizontaler Blockrichtung
      int signature = blocks[i].signature; // Blocktyp
      int angle = blocks[i].angle;         // Drehwinkel von Colorcodes
      int area = height * width;           // Blockgröße
      switch (signature)
      { // Was sehe ich?
      case SIGNATURE_BALL:
        blockCountBall++;
        if (area > ballAreaMax) // Der neue Block ist relevanter und überschreibt
        {
          ballAreaMax = area;
          io.ball.set(x);          // merke Ballwinkel
          io.ballWidth.set(width); // merke Ballbreite
          io.ballArea.set(area);   // merke Ballgröße
          io.seeBall.now();        // merke Sichtungszeit des Balls
          if (width > BALL_WIDTH_TRIGGER)
            io.closeBall.now(); // merke ggf. Sichtungszeit eines nahen Balls
        }
        break;
      case SIGNATURE_GOAL:
        blockCountGoal++;
        if (area > goalAreaMax) // Der neue Block ist relevanter und überschreibt
        {
          goalAreaMax = area;
          io.goal.set(x);          // merke Torwinkel
          io.goalWidth.set(width); // merke Torbreite
          io.goalArea.set(area);   // merke Torgröße
          io.seeGoal.now();        // merke Sichtungszeit des Tors
        }
        break;
      }
    }
}

tObject getBall();
tObject getGoal();
int getGoalPos();

    
    // Liest alle Blöcke aus und zählt diese
    // Sendet "cs error" über USB bei Fehler in Prüfsumme eines empfangenen Objekts

    
    endSegment();
  }
}

bool Camera::isEnabled()
{
  return CAMERA_ENABLED;
}

Camera camera;