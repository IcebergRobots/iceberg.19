#include "Pui.h"

/*****************************************************
  create a physical user interface
*****************************************************/
Pui::Pui() {}

/*****************************************************
  initialise communication
*****************************************************/
void Pui::init() {
  beginSegment("pui");
  //I2c.write(ADDRESS, A_PINMODE, 0x00); // set OUTPUT
  I2c.write(ADDRESS, B_PINMODE, 0xFF);  // set INPUT
  I2c.write(ADDRESS, B_VALUE, 0xFF);    // set INPUT_PULLUP
  endSegment();
}

/*****************************************************
  output a signal on the pui pin
  @param _value: output signal
*****************************************************/
void Pui::set(byte pin, bool value) {
  if(pin < 8) {
    bitWrite(a, pin, value);
    I2c.write(ADDRESS, A_VALUE, a);
  }
}

/*****************************************************
  return the temporary saved pui pin signal
*****************************************************/
bool Pui::get(byte pin) {
  if(pin < 8) return bitRead(a, pin);
  else return bitRead(b, pin-8);
}

/*****************************************************
  read all pui pins
*****************************************************/
void Pui::update() {
  I2c.read(ADDRESS, A_VALUE, 1);
  b = I2c.receive();
}

Pui pui = Pui();