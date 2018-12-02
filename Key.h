#ifndef Key_h
#define Key_h

#include "Core.h"

/***********************************************************
																	click
								 ┌─────────┬────────┴──────┬───────────────┬─╌                                                
							stroke   permanent       permanent       permanent    
			on╔════════╪═════════╪═══════════════╪═══════════════╪═════ ... ═╗
Button  ║        ┊         ┊               ┊               ┊           ║
		 off║        ┊         ┊               ┊               ┊           ║
════════╝        ┊postDelay┊               ┊               ┊           ╚══════                
				┊preDelay┊         ┊repititionDelay┊repititionDelay┊                                             

************************************************************/

class Key
{
	public:
		Key(int _pin);
		Key(int _pin, unsigned long _preDelay);
		Key(int _pin, unsigned long _preDelay, unsigned long _postDelay);
		Key(int _pin, unsigned long _preDelay, unsigned long _postDelay, unsigned long _repititionDelay);
		bool stroke();
		bool permanent();
		bool click();
		void update();
	private:
		void cooldown(unsigned long delay);
		int pin = 0;
		bool active = false;
		unsigned long clicks = 0;
		unsigned long preDelay = 0;
		unsigned long postDelay = -1;        // infinity
		unsigned long repititionDelay = -1;  // infinity
		unsigned long cooldownTimer = 0;
};
#endif