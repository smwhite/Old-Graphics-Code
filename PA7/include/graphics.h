#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"

class Graphics
{
  public:
    Graphics(string vFile, string fFile, string mFile);
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt, bool rotation,bool translation,int pause,bool moonR,bool moonT, int moonP, float LR,float UD);
    void Render();

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
	GLint m_gSampler;

    Object *m_cube;
	Object *m_moon;
    glm::mat4 cubeLocation;

    string vertexFile;
    string fragmentFile;
    string modelFile;
};

#endif /* GRAPHICS_H */
