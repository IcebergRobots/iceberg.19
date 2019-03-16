#include "Camera.h"

/*********************************************************************
  Constructor
*********************************************************************/
Camera::Camera()
{
  setLocked(30);    // begrenze die Abfragehäufigkeit, um die Framerate der Kamera nicht zu überschreiten
  setCooldown(100); // die Kamera muss nicht so häufig aktualisiert werden
}

/*********************************************************************
  initialisiert die SPI Kommunikation
*********************************************************************/
void Camera::init()
{
  if (isEnabled())
  {
    beginSegment(F("c"));
    SPI.begin(); // initialisiere den SPI Bus
    Pixy::init();
    if (SPI.transfer(0x00) == 255)
      io.cameraResponse.now(); // erkennen, ob die Kamera angeschlossen ist
    endSegment();
  }
  else
    debug(F("-c"));
}

void Camera::frame()
{
  if (isEnabled())
  {
    beginSegment(F("c:r"));
    if (io.turbo.on())
      setLED(0, 0, 0);     // schalte die Front-LED aus
    int ballAreaMax = 0;   // Ballgröße, 0: blind, >0: Flächeninhalt
    int goalAreaMax = 0;   // Torgröße,  0: blind, >0: Flächeninhalt
    int eastHeightMax = 0; // Farbmarkierungsgröße,  0: blind, >0: Flächeninhalt
    int westHeightMax = 0; // Farbmarkierungsgröße,  0: blind, >0: Flächeninhalt

    blockCount = getBlocks();
    blockCountBall = 0;
    blockCountGoal = 0;
    // Liest alle Blöcke aus und zählt diese
    // Sendet "cs error" über USB bei Fehler in Prüfsumme eines empfangenen Objekts

    for (byte i = 0; i < blockCount; i++)
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
    endSegment();
  }
}

bool Camera::isEnabled()
{
  return CAMERA_ENABLED;
}

Camera camera;