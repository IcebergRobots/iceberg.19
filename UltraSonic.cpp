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

void Ultrasonic::init() {
  beginSegment("us");
  for(int i = 0; i < 5; i++) {
    Wire.beginTransmission(addresses[i]);
    Wire.write(byte(0x02));
    Wire.write(byte(70));
    Wire.endTransmission();
  }
  endSegment();
}

void Ultrasonic::update() {
  beginSegment("us");
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
}
bool Ultrasonic::isEnabled() {
  return true;
}

Ultrasonic us;