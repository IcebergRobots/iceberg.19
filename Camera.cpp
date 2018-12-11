#include "Camera.h"

/*********************************************************************
- Konstruktor
*********************************************************************/
Camera::Camera() {}

/*********************************************************************
- initialisiert die SPI Kommunikation
*********************************************************************/
void Camera::init() {  
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setDataMode(SPI_MODE0);
}

void Camera::frame() {
  //io.spiCs.set(LOW);
  delay(1); // Give the OpenMV Cam some time to setup to send data.

  if(SPI.transfer(1) == 85) { // saw sync char?
    SPI.transfer(&temp, 4); // get length
    int zero_legnth = 4 + ((temp + 1) % 4);
    if (temp) {
      SPI.transfer(&buff, min(temp, BUFFER_SIZE));
      temp -= min(temp, BUFFER_SIZE);
    }
    while (temp--) SPI.transfer(0); // eat any remaining bytes
    while (zero_legnth--) SPI.transfer(0); // eat zeros.
  }

  //io.spiCs.set(HIGH);
  debugln(buff);
}

Camera camera = Camera();