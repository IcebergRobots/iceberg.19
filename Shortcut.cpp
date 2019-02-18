#include "Shortcut.h"

/*****************************************************
  combine keys to a shortcut
  @param _keys: two dimensional array of key pointers:
    - create array: Key *array = {&key1, &key2, ...};
    - insert array
  @param _keysLength: 
    - length of the keys array
    - number of keys in the shortcut
  @param _muteKeys: if the shortcut is active, should the individual keys detect clicks?
  @param _preStroke: delay befor the first shortcut click
  @param _postStroke: delay after the first shortcut click
  @param _postFurther: delay after second or later shortcut click
*****************************************************/
Shortcut::Shortcut(Key **_keys, byte _keysLength, bool _muteKeys, unsigned long _preStroke, unsigned long _postStroke, unsigned long _postFurther)
 : Key(0, VIRTUAL, _preStroke, _postStroke, _postFurther) {
  setElementType(SHORTCUT);
  keys = _keys;
  keysLength = _keysLength;
  muteKeys = _muteKeys;
}

/*****************************************************
  scan all individual keys and process to detect clicks
*****************************************************/
void Shortcut::update() {
  debug("s", false);
  set(true); // activate virtual key
  for(int i = 0; i < keysLength; i++) {
    if (keys[i]->off()) { // this key inactive
      set(false); // shortcut is inactive
      break; // skip other keys
    }
  }
  if(on() && muteKeys) {
    for(int i = 0; i < keysLength; i++) {
      keys[i]->set(false); // deactivate key to prevent their functions 
      keys[i]->update();
    }
  }
  Key::update(); // is this shortcut active (stroke, further, click)?
}