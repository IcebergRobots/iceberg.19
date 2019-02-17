#ifndef Shortcut_h
#define Shortcut_h

#include "Key.h"

#define MUTE_KEYS true
#define FIRE_KEYS false

class Shortcut: public Key
{
	public:
		Shortcut(Key **_keys, byte _keysLength, bool _muteKeys, unsigned long _preStroke=INF, unsigned long _postStroke=INF, unsigned long _postFurther=INF);
    void update();
	private:
		Key **keys;
    byte keysLength = 0;
    bool muteKeys = false;
};

#endif