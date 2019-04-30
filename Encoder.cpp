#include "Encoder.h"
#include "HardWire.h"


Encoder::Encoder(int nr){
  switch(nr){
    case 0 : encNr = 8; dataNr = 0; break;
    case 1 : encNr = 9; dataNr = 0; break;
    case 2 : encNr = 8; dataNr = 1; break;
    case 3 : encNr = 9; dataNr = 1; break;  
  }
}

void Encoder::update(){
  int speed;
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

int Encoder::getSpeed(){
  return speed;
}

int Encoder::getPwr(int pwr, int motor){
    int speed;
    int currentspeed = getSpeed();
    currentspeed = currentspeed - 127;
    speed = 1/3 * pwr + 3 * currentspeed;
    return currentspeed;
}