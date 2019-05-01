#include "Encoder.h"
#include "HardWire.h"
#include "Config.h"


Encoder::Encoder(){

}

void Encoder::update(){
  if(millis() - timer > MAXTIME){
    Wire.requestFrom(ENCODER1_ID,2);
    if(Wire.available()){
      speed[0] = Wire.read();
      speed[3] = Wire.read();
    }
    Wire.requestFrom(ENCODER2_ID,2);
    if(Wire.available()){
      speed[0] = Wire.read();
      speed[3] = Wire.read();
    }
    timer = millis();
  } 
}

int Encoder::getSpeed(int id){
  return speed[id];
}


