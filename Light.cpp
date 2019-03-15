#include "Light.h"

/*****************************************************
  Constructor
*****************************************************/
Light::Light() {
  setCooldown(10);
  pui.setCooldown(10);
  line.setCooldown(100);
  inside.setCooldown(100);
}

void Light::init() {
  beginSegment(F("l"));
  io.indHeartbeat.set(255);
  io.indFront.set(255);
  io.indLeft.set(255);
  io.indRight.set(255);
  if (pui.onDemand()) {
    pui.setAllColor(255, 255, 255);
    pui.show();
  }
  if (line.onDemand()) {
    line.setAllColor(255, 255, 255);
    line.show();
  }
  io.setupLight.set();
  endSegment();
}

void Light::light() {
  io.indHeartbeat.set(map(abs(int(millis() % 500) - 250), 0, 250, -100, 356));

  if (io.setupLight.off()) {
    io.indFront.set(io.seeBall.get());
    io.indLeft.set(0);
    io.indRight.set(0);

    if (inside.onDemand()){
      //animatio
      if(io.animationEnabled.get()){
        for(int i = 0; i<8; i++){
          inside.setPixelColor(i, inside.wheelToColor( (i*255/8 + millis()/4)%255 ));
        }
        inside.setBrightness(255);
        inside.show();
      }
      //NO animation
      else{
        for(int i = 0; i<8; i++){
          inside.setPixelColor(i, 0, 0, 0);
        }
        inside.setBrightness(255);
        inside.show();
      }
    }

    if (line.onDemand()) {
      
      if(io.animationEnabled.get()){
        line.setCooldown(10);
      }else{
        line.setCooldown(100);
      }

      // NO animation part
      if(! io.animationEnabled.get()){
        for (int i = 0; i <= 39; i++) {
          if (i >= 32)
            line.setPixelColor(i, 255, 255, 255);
          else
            line.setPixelColor(i, 0, 0, 0);
        }

        line.setBrightness(255);
        line.show();
      }
      // animation part
      else{
        int werte = io.animationState.get();

        for(int beta=0; beta<40; beta++){
          if(beta < 32){
            line.setPixelColor(beta, line.wheelToColor( ((3-(beta%4))*64 + ((millis()/3)%255) % 255 ) ) );
          }
          else{
            line.setPixelColor(beta, line.wheelToColor( ((millis()/3)%255) % 255           ) );
          }
        }
        line.setBrightness(255);
        line.show();
      }
    }

    if (pui.onDemand()) {
      //NO Animation
      if(! io.animationEnabled.get()){
        pui.setPixelColor(0, pui.wheelToColor((byte) millis() % 255 ));
        pui.setPixelState(0, digitalRead(io.lineInterrupt.getPin()));
        pui.setPixelState(1, io.battery.on());
        pui.setPixelState(2, io.seeMate.on(), true);
        pui.setPixelState(3, io.seeGoal.on(), true);
        if (io.hasBall.on())              pui.setPixelState(4, 1);
        else if (io.seeBall.on())             pui.setPixelState(4, 2);
        else                                  pui.setPixelState(4, 0, true);
        pui.setPixelState(5, io.flat.on());
        if (io.turbo.off() || !DEBUG_ENABLED) pui.setPixelState(6, 1);
        else if (DEBUG_LOOP || DEBUG_SEGMENT) pui.setPixelState(6, 3);
        else                                  pui.setPixelState(6, 2);
        pui.setPixelState(7, io.onLine.on());
        pui.setPixelState(8, io.kicker.on());
        pui.setPixelState(9, io.bluetooth.on());
        if (io.motor.off()) pui.setPixelState(10, 0);
        else if (io.pause.on()) pui.setPixelState(10, 2);
        else pui.setPixelState(10, 1);
        pui.setPixelState(11, io.headstart.on());
        

        pui.setBrightness(map(io.poti.get(), 0, 1023, 0, 255));
        pui.show();
      }

      //Animation
      else{

        for(int i = 0; i<12; i++){
          pui.setPixelColor(i, pui.wheelToColor( (i*255/12 + millis()/4)%255 ));
        }
        pui.setBrightness(255);
        pui.show();
      }
    }
  }
}

bool Light::isEnabled() {
  return true;
}

Light light;
