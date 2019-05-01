#include "Encoder.h"
#include "HardWire.h"
#include "Config.h"


Encoder::Encoder(int encNr, int dataNr){
   _encNr = encNr;
   _dataNr = dataNr;
}

void Encoder::update(){
  if(millis() - timer > maxtime){
    Wire.requestFrom(_encNr,2);
    if(Wire.available()){ 
      if(_dataNr = 1){
        Wire.read();
        speed = Wire.read();
      }else{
        speed = Wire.read();
      }
    }
    timer = millis();
  } 
}

int Encoder::getSpeed(){
  return speed;
}


