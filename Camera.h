#ifndef Camera_h
#define Camera_h

#include "core.h"

#define BUFFER_SIZE 128

class Camera
{
  public:
    Camera();
    void init();
    void frame();
    
  private:
    int32_t temp = 0;
    char buff[BUFFER_SIZE] = {0};
};
extern Camera camera;

#endif
