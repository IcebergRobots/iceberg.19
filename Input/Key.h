#ifndef Key_h
#define Key_h

#include "Pin.h"

/******************************************************************************
                                  click
                  ┌──────────┬──────┴──────┬─────────────┬─╌                                                
               stroke     further       further       further    
      on╔═════════╪══════════╪═════════════╪═════════════╪═════ ... ═╗
Button  ║         ┊          ┊             ┊             ┊           ║
     off║         ┊          ┊             ┊             ┊           ║
════════╝         ┊postStroke┊             ┊             ┊           ╚══════                
        ┊preStroke┊          ┊ postFurther ┊ postFurther ┊      ...  ┊                 
        ┊         ┊          ┊             ┊             ┊           ┊
state:  ┊        STROKE    FURTHER       FURTHER       FURTHER       ┊
  OFF   ┊  OFF    ┊   ON     ┊       ON    ┊       ON    ┊      ...  ┊  OFF

******************************************************************************/
class Key: public Pin
{
	public:
    Key(byte _pin, byte _type, unsigned long _preStroke=INF, unsigned long _postStroke=INF, unsigned long _postFurther=INF);
		bool stroke();
		bool further();
		bool click();
		void update();
	private:
    byte state = OFF; // OFF, ON, STROKE, FURTHER
		unsigned long clicks = 0;
		unsigned long preStroke = INF;   // by default set to infinity
		unsigned long postStroke = INF;  // by default set to infinity
		unsigned long postFurther = INF; // by default set to infinity
};

#endif