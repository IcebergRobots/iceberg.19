#include "Key.h"

/*****************************************************
  configurate an arduino pin as a key
  @param _pin: pin address
  @param _type: type of pin (ANALOG, DIGITAL, PWM, PUI, VIRTUAL)
  @param _preStroke: delay befor the first click
  @param _postStroke: delay after the first click
  @param _postFurther: delay after second or later click
  - see header file for visualisation
*****************************************************/
Key::Key(byte _pin, byte _type, unsigned long _preStroke, unsigned long _postStroke, unsigned long _postFurther)
 : OwnPin(_pin, INPUT_PULLUP, _type) {
  setElementType(KEY);
  preStroke = _preStroke;
  postStroke = _postStroke;
  postFurther = _postFurther;
}

/*****************************************************
  is there a first click?
*****************************************************/
bool Key::stroke() { return state == STROKE; }
/*****************************************************
  is there a second or later click?
*****************************************************/
bool Key::further() { return state == FURTHER; }
/*****************************************************
  is there any click?
*****************************************************/
bool Key::click() { return stroke() || further(); }

/*****************************************************
  read the arduino pins and process it to detect clicks
*****************************************************/
void Key::update() {
  OwnPin::update();
	if(off()) state = OFF; // Knopf ist losgelassen
	else { // Knopf wird gedrückt
    switch (state) {
      default:
      case OFF: // so far no click was detected
        if (outsidePeriod(preStroke)) {
          state = STROKE; // detect the first click
          now(); // create an event and save click time
        }
        break;
      case ON:
      case STROKE:
        if (outsidePeriod(postStroke)) {
          state = FURTHER;  // detect a further click
          now(); // create an event and save click time
        } else state = ON;
        break;
      case FURTHER:
        if (outsidePeriod(postFurther)) {
          state = FURTHER;  // detect a further click
          now(); // create an event and save click time
        } else state = ON;
        break;
    }
	}
}