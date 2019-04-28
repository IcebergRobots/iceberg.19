#include "Ultrasonic.h"

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
  erfragt beim Ultraschallsensor durch einen Interrupt die aktuellen Sensorwerte
  empfängt und speichern diese Werte im globalen Array us[]:
      1
     .--.
    /    \ 
  2 \    / 0
     '--'
      3
*****************************************************/

byte Ultrasonic::right() {
  //TODO
}

byte Ultrasonic::front() {
  //TODO
}

byte Ultrasonic::left() {
  //TODO
}

byte Ultrasonic::back() {
  //TODO
}

bool Ultrasonic::check() {
  //TODO
}

void Ultrasonic::update(){
  //TODO
}