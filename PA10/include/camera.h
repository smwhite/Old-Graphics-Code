#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    bool Update(float LR,float UD,float ELR, float EUD, float ZOOM);
  
  private:
    glm::mat4 projection;
    glm::mat4 view;
	/*float UD = 0;
	float LR = 0;
	float ELR = 0;
	float EUD = 0;*/
};

#endif /* CAMERA_H */
