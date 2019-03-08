#ifndef Light_h
#define Light_h

#include "IO.h"
#include "Reflexion.h"
#include "Demand.h"
#include "LightBoard.h"

class Light : public Demand
{
  public:
    Light();
    void init();
    void light();
    
    bool isEnabled();

    LightBoard pui = LightBoard(12, 32, 10, 100);
    LightBoard line = LightBoard(40, 46, 10, 100);

  private:
};
extern Light light;

#endif
