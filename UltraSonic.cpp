#include "Ultrasonic.hpp"

// Implementierung: OBJEKTE
extern Display d;
extern Player p;
extern Led led;
extern Mate mate;
extern Pilot m;
//extern Ultrasonic us;

Ultrasonic::Ultrasonic() {
  
}

/*****************************************************
  initiiert Ultraschallsensoren
*****************************************************/
void Ultrasonic::init(){
  for(int i = 0; i < 5; i++) {
    Wire.beginTransmission(addresses[i]);
    Wire.write(byte(0x02));
    Wire.write(byte(70));
    Wire.endTransmission();
  }
}

/*****************************************************
  holt letze Werte ab
*****************************************************/
void Ultrasonic::fetch() {
  for(int i = 0; i < 5; i++) {
    Wire.beginTransmission(addresses[i]);
    Wire.write(byte(0x02));
    Wire.endTransmission();
    Wire.requestFrom((int) addresses[i], (int) 2);

    if (2 <= Wire.available()) { 
        distance[i] = Wire.read() << 8;    
        distance[i] |= Wire.read(); 
    }
  }

  Wire.beginTransmission(addresses[1]);
  Wire.write(byte(0x04));
  Wire.endTransmission();
  Wire.requestFrom((int) addresses[1], (int) 2);

  if (2 <= Wire.available()) { 
    echo2[0] = Wire.read() << 8;    
    echo2[0] |= Wire.read(); 
  }

  Wire.beginTransmission(addresses[3]);
  Wire.write(byte(0x04));
  Wire.endTransmission();
  Wire.requestFrom((int) addresses[3], (int) 2);

  if (2 <= Wire.available()) { 
    echo2[1] = Wire.read() << 8;    
    echo2[1] |= Wire.read(); 
  }

  Wire.beginTransmission(addresses[1]);
  Wire.write(byte(0x06));
  Wire.endTransmission();
  Wire.requestFrom((int) addresses[1], (int) 2);

  if (2 <= Wire.available()) { 
    echo3[0] = Wire.read() << 8;    
    echo3[0] |= Wire.read(); 
  }

  Wire.beginTransmission(addresses[3]);
  Wire.write(byte(0x06));
  Wire.endTransmission();
  Wire.requestFrom((int) addresses[3], (int) 2);

  if (2 <= Wire.available()) { 
    echo3[1] = Wire.read() << 8;    
    echo3[1] |= Wire.read(); 
  }
  
}

/*****************************************************
  Wenn Timer entsprechend: löst neue Messung aus und holt alte Werte ab.
*****************************************************/
void Ultrasonic::update() {
  if(millis()-lastMeasurement > 25 && !fetched){
    fetch();
    fetched = true;
  }
  if(millis()-lastMeasurement > 65){
    Wire.beginTransmission(0);  //auf Adresse 0 hören alle Ultraschallsensor zu. Alternativ können die Befehle an alle Sonsoren einzeln gesendet werden.
    Wire.write(byte(0x00));
    Wire.write(byte(0x51));
    Wire.endTransmission();

    lastMeasurement = millis();
    fetched = false;
  }
}

/*****************************************************
  erfragt beim Ultraschallsensor durch einen Interrupt die aktuellen Sensorwerte
  empfängt und speichern diese Werte im globalen Array us[]:
      1
     .--.
    /    \ 
  2 \    / 0
     '--'
      3
*****************************************************/

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


bool Ultrasonic::check() {
  //TODO
}