#include "Ultrasonic.h"

Ultrasonic::Ultrasonic() {
  setLocked(25);
  setCooldown(65);
}

int Ultrasonic::frontLeft()  {  return distance[0];  }
int Ultrasonic::left()       {  return distance[1];  }
int Ultrasonic::back()       {  return distance[2];  }
int Ultrasonic::right()      {  return distance[3];  }
int Ultrasonic::frontRight() {  return distance[4];  }
int Ultrasonic::front()      {  return min(frontLeft(), frontRight());  }
int Ultrasonic::left2()      {  return echo2[0];     }
int Ultrasonic::right2()     {  return echo2[1];     }
int Ultrasonic::left3()      {  return echo3[0];     }
int Ultrasonic::right3()     {  return echo3[1];     }
int Ultrasonic::getx()       {  return x;            }
int Ultrasonic::gety()       {  return y;            }


void Ultrasonic::init() {
  beginSegment(F("us"));
  for(int i = 0; i < 5; i++) {
    Wire.beginTransmission(addresses[i]);
    Wire.write(byte(0x02));
    Wire.write(byte(70));
    Wire.endTransmission();
  }
  endSegment();
}

void Ultrasonic::update() {
  beginSegment(F("us"));
  fetch();
  for(int i = 0; i < 5; i++) {
    Wire.beginTransmission(addresses[i]);
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();
  }
  endSegment();
}

void Ultrasonic::fetch() {
  for(int i = 0; i < 5; i++) {
    Wire.beginTransmission(addresses[i]);
    Wire.write(byte(0x02));
    Wire.endTransmission();
    Wire.requestFrom(addresses[i], 2);

    if (2 <= Wire.available()) { 
        distance[i] = Wire.read() << 8;    
        distance[i] |= Wire.read(); 
    }
  }

  Wire.beginTransmission(addresses[1]);
  Wire.write(byte(0x04));
  Wire.endTransmission();
  Wire.requestFrom(addresses[1], 2);

  if (2 <= Wire.available()) { 
    echo2[0] = Wire.read() << 8;    
    echo2[0] |= Wire.read(); 
  }

  Wire.beginTransmission(addresses[3]);
  Wire.write(byte(0x04));
  Wire.endTransmission();
  Wire.requestFrom(addresses[3], 2);

  if (2 <= Wire.available()) { 
    echo2[1] = Wire.read() << 8;    
    echo2[1] |= Wire.read(); 
  }

  Wire.beginTransmission(addresses[1]);
  Wire.write(byte(0x06));
  Wire.endTransmission();
  Wire.requestFrom(addresses[1], 2);

  if (2 <= Wire.available()) { 
    echo3[0] = Wire.read() << 8;    
    echo3[0] |= Wire.read(); 
  }

  Wire.beginTransmission(addresses[3]);
  Wire.write(byte(0x06));
  Wire.endTransmission();
  Wire.requestFrom(addresses[3], 2);

  if (2 <= Wire.available()) { 
    echo3[1] = Wire.read() << 8;    
    echo3[1] |= Wire.read(); 
  }
  
}

bool Ultrasonic::validate() {
  if (left() + right() >= 165 && left() + right() <= 195){
    return true;
  }
  return false;
}

void Ultrasonic::position() {
  x = ((left() - 20) + (142 - right())) / 2;
  if (front() + back() < 180)     {     y = back() + 10;       }
  if (front() + back() >= 180)    {     y = back() - 20;       }
}

bool Ultrasonic::isEnabled() {
  return true;
}

Ultrasonic us;
