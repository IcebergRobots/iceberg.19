#include "Encoder.h"
#include "HardWire.h"


Encoder::Encoder(int encNr, dataNr){
   _encNr = encNr;
   _dataNr = dataNr;
}

void Encoder::update(){
  unsigned long timer = millis;
  if(timer - millis > maxtime){
    Wire.requestFrom(encNr,2);
    if(Wire.available()){ 
      if(dataNr = 1){
        Wire.read();
        speed = Wire.read();
      }else{
        speed = Wire.read();
      }
    }
  } 
}

int Encoder::getSpeed(){
  return speed;
}


