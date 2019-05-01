#include "Bluetooth.hpp"

/*********************************************************************
  Constructor
*********************************************************************/

Bluetooth::Bluetooth(HardwareSerial *_serial){
    bluetoothSerial = _serial;
}

/*********************************************************************
  Methoden für Bluetooth
*********************************************************************/

bool Bluetooth::send(String function, String values[]){
    bluetoothSerial->write(functionbyte(function, values));
    bluetoothSerial->write(checkbyte(values);
    for(int i=0; i<sizeof(values); i++){
      bluetoothSerial->write(valuetobyte(values[i]));
    } 
}

bool Bluetooth::update(){
  bool updated;
  while(bluetoothSerial->available()){
    tempbuffer = bluetoothSerial->read();
    if(process(tempbuffer)){
      updated = true;
    }else{
      updated = false;
    }
  }
  return updated;
}

bool Bluetooth::process(byte currentbyte){
  bool processed;
  byte buffer[6];
  int expectedbytes;
  if((10000000 & currentbyte) != 0){
    expectedbytes = processvalues(currentbyte);
    buffer[0] = currentbyte;
    return true;
  } else if((00000000 & currentbyte) == 0){
    if(expectedbytes == 1){
      buffer[1] = currentbyte;
      return true;
    } else if(expectedbytes < 1){
      buffer[expectedbytes] = currentbyte;
      return true;
    }
  } else {
    return false;
  }
  return processed;
}

void Bluetooth::extract(){

}

char Bluetooth::functionbyte(int function, int values[]){
    char requiredbyte; 
    switch(function){
      case 0: requiredbyte = 10001000;
                break;
      case 1: requiredbyte = 10010000;
                break;
    }
    if(sizeof(values) == 1){ 
      requiredbyte = requiredbyte | 00000001;
    } else if(sizeof(values) == 2){ 
      requiredbyte = requiredbyte | 00000010;
    } else if(sizeof(values) == 3){ 
      requiredbyte = requiredbyte | 00000011;
    }
    return requiredbyte;
}

byte Bluetooth::valuetobyte(int value){
  byte _value;
  _value = byte(value);
  return _value;
}

byte Bluetooth::checkbyte(int values[]){
  byte check;
  int sum = 0;
  for(int i=0; i<sizeof(values); i++){
    sum += values[i];
  }
  sum = sum % 255 + 1;
  check = byte(sum);
  return check;
}

int Bluetooth::processvalues(byte currentbyte){
  byte valuebyte  = currentbyte & 00000111;
  return valuebyte; 
}






