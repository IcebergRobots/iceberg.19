#ifndef Timer_h
#define Timer_h

#include "Value.h"

class Timer : public Value
{
  public:
    Timer(unsigned long _surviveTime=0, Timer *_requirement=NULL);
    void setSurviveTime(unsigned long _surviveTime);
    void update();
    void set(bool active=true);
  private:
    unsigned long surviveTime = 0;
    Timer *requirement;
};

#endif