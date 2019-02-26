#include "Orientation.h"

/*********************************************************************
  Constructor
*********************************************************************/
Orientation::Orientation(){
    setCooldown(100);
}

void Orientation::init() {
  if (isEnabled()) {
    beginSegment("o");
    BNO_Init(&bno);
    bno055_set_operation_mode(OPERATION_MODE_NDOF);
    endSegment();
  } else {
    debug("-o");
  }
}

void Orientation::update() {
  if (isEnabled()) {
    beginSegment("o");
    struct bno055_euler myEulerData;
    bno055_read_euler_hrp(&myEulerData);
    io.xOrientation.set(float(myEulerData.p) / 16.00);
    io.yOrientation.set(float(myEulerData.r) / 16.00);
    io.zOrientation.set(float(myEulerData.h) / 16.00);
    io.heading.set(io.zOrientation.get() - io.headingOffset.get());

    if (io.xOrientation.change() || io.yOrientation.change() || io.zOrientation.change()) {
      if (DEBUG_SEGMENT) {
        debug(io.xOrientation.str(4) + ",");
        debug(io.yOrientation.str(4) + ",");
        debug(io.zOrientation.str(4));
      }
      d.request();
    }
    endSegment();
  }
}

bool Orientation::isEnabled() {
  return ORIENTATION_ENABLED && io.battery.on();
}

Orientation orientation;
