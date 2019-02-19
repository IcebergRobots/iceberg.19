#include "Orientation.h"

/*********************************************************************
  Constructor
*********************************************************************/
Orientation::Orientation() : Adafruit_BNO055(55) {
    setCooldown(100);
}

void Orientation::init() {
  if (isEnabled()) {
    beginSegment("o");
    if (!begin()) debug("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    endSegment();
  } else {
    debug("-o");
  }
}

void Orientation::update() {
  if (isEnabled()) {
    sensors_event_t event;
    getEvent(&event);
    io.xOrientation.set(event.orientation.x);
    io.yOrientation.set(event.orientation.y);
    io.zOrientation.set(event.orientation.z);
  }
}

bool Orientation::isEnabled() {
  return ORIENTATION_ENABLED && io.battery.on() && false;
}

Orientation orientation;