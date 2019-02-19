#include "Light.h"

/*****************************************************
  Constructor
*****************************************************/
Light::Light() {
  setLocked(10);
}

void Light::init() {
  io.indHearbeat.set(255);
  io.indFront.set(255);
  io.indLeft.set(255);
  io.indRight.set(255);
  io.setupLight.set();
}

void Light::light() {
  io.indHearbeat.set(map(abs(int(millis() % 500) - 250),0,250,-100,356));

  if (io.setupLight.off()) {
    io.indFront.set(io.seeBall.get());
    io.indLeft.set(0);
    io.indRight.set(0);
  }
 
  pui.setAllColor(255, 255, 255);
  pui.setBrightness(map(io.poti.get(), 0, 1023, 0, 255));
  if (pui.onDemand()) pui.show();
  /*showState(puiBoard, 0, io.start.get());
  showState(puiBoard, 1, io.stop.get());
  showState(puiBoard, 2, io.record.get());
  showState(puiBoard, 3, io.start.stroke());
  showState(puiBoard, 4, io.stop.stroke());
  showState(puiBoard, 5, io.record.stroke());*/
}

bool Light::isEnabled() {
  return true;
}

Light light;