#ifndef Light_h
#define Light_h

#include "IO.h"
#include "Demand.h"
#include "LightBoard.h"

class Light : public Demand
{
  public:
    Light();
    void init();
    void light();
    
    bool isEnabled();

    LightBoard pui = LightBoard(12, io.puiLight, 10, 100);

  private:
};
extern Light light;

#endif
