#ifndef Timer_h
#define Timer_h

#include "Value.h"

class Timer : public Value
{
  public:
    Timer(unsigned long _surviveTime=0, Timer *_requirement=NULL);
    void setSurviveTime(unsigned long _surviveTime);
    void update();
    
    void now();
    void now(String reason);
    void abort();

    String str(unsigned int minLength=0, unsigned int maxLength=INF, bool sign=false);
  private:
    void refresh();
    unsigned long surviveTime = 0;
    Timer *requirement;

    using Value::now;
    using Value::abort;
    using Value::setWithoutEvent;
    using Value::set;
    using Value::set;
    using Value::add;
    using Value::mul;
    using Value::toggle;
    using Value::setLow;
    using Value::setHigh;
};

#endif