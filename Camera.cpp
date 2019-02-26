#include "Camera.h"

/*********************************************************************
  Constructor
*********************************************************************/
Camera::Camera() {
    setLocked(30);
    setCooldown(100);
}

/*********************************************************************
  initialisiert die SPI Kommunikation
*********************************************************************/
void Camera::init() { 
    if (isEnabled()) {
        beginSegment("c");
        SPI.begin();
        Pixy::init();
        io.cameraResponse.set(SPI.transfer(0x00) == 255);
        endSegment();
    } else debug("-c");
}

void Camera::frame() {
    if (isEnabled()) {
        beginSegment("c:r");
        if (io.turbo.on()) setLED(0, 0, 0); // schalte die Front-LED aus
        int ballAreaMax = 0;  // Ballgröße, 0: blind, >0: Flächeninhalt
        int goalAreaMax = 0;  // Torgröße,  0: blind, >0: Flächeninhalt
        int eastHeightMax = 0;  // Farbmarkierungsgröße,  0: blind, >0: Flächeninhalt
        int westHeightMax = 0;  // Farbmarkierungsgröße,  0: blind, >0: Flächeninhalt

        blockCount = getBlocks();
        blockCountBall = 0;
        blockCountGoal = 0;
        // Liest alle Blöcke aus und zählt diese
        // Sendet "cs error" über USB bei Fehler in Prüfsumme eines empfangenen Objekts

        for (byte i = 0; i < blockCount; i++) { // geht alle erkannten Bloecke durch
            int height = blocks[i].height;
            int width = blocks[i].width;
            int x = blocks[i].x - X_CENTER;
            int signature = blocks[i].signature;
            int angle = blocks[i].angle;
            int area = height * width;
            switch (signature) { // Was sehe ich?
                case SIGNATURE_BALL:
                    blockCountBall++;
                    if (area > ballAreaMax) {
                        ballAreaMax = area;
                        io.ball.set(x);           // merke Ballwinkel
                        io.ballWidth.set(width);  // merke Ballbreite
                        io.ballArea.set(area);    // merke Ballgröße
                        io.seeBall.set();
                        io.closeBall.set(width > BALL_WIDTH_TRIGGER);
                    }
                break;
                case SIGNATURE_GOAL:
                    blockCountGoal++;
                    if (area > goalAreaMax) {
                        goalAreaMax = area;
                        io.goal.set(x);           // merke Torwinkel
                        io.goalWidth.set(width);  // merke Torbreite
                        io.goalArea.set(area);    // merke Torgröße
                        io.seeGoal.set();
                    }
                break;
            }
        }
        endSegment();
    }
}

bool Camera::isEnabled() {
    return CAMERA_ENABLED;
}

Camera camera;