#ifndef Bluetooth_h
#define Bluetooth_h

#include "core.h"
#include "Arduino.h"

class Bluetooth
{
  public:
    Bluetooth(HardwareSerial *_serial);
    bool extractMessage(String input, String * output);
    void send(String input);
    bool update();
    String getMessage();

  private:
    bool capture;
    String buffer;
    String lastMessage;
    HardwareSerial *bluetoothSerial;
};
extern Bluetooth bluetooth;

#endif