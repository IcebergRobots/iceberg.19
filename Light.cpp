#include "Light.h"

/*****************************************************
  Constructor
*****************************************************/
Light::Light() {
  setCooldown(10);
  pui.setCooldown(10);
  line.setCooldown(100);
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
 
  line.setAllColor(255, 255, 255);
  line.setBrightness(map(io.poti.get(), 0, 1023, 0, 100));
  if (line.onDemand()) line.show();

  //pui.setAllColor(255, 255, 255);
  pui.setPixelState(0, 0, true);
  pui.setPixelState(1, io.battery.on());
  pui.setPixelState(2, io.seeMate.on(), true);
  pui.setPixelState(3, io.seeGoal.on(), true); 
  pui.setPixelState(4, io.seeBall.on(), true); 
  pui.setPixelState(5, io.flat.on());
  if (io.turbo.off() || !DEBUG_ENABLED) pui.setPixelState(6, 1);
  else if (DEBUG_LOOP || DEBUG_SEGMENT) pui.setPixelState(6, 3);
  else                                  pui.setPixelState(6, 2);
  pui.setPixelState(7, io.bottom.on()); 
  pui.setPixelState(8, io.kicker.on()); 
  pui.setPixelState(9, io.bluetooth.on()); 
  pui.setPixelState(10, io.motor.on()); 
  pui.setPixelState(11, io.headstart.on()); 

  pui.setBrightness(map(io.poti.get(), 0, 1023, 0, 100));
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
