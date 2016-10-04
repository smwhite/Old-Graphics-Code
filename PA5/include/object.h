#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"

class Object
{
  public:
    Object(glm::mat4 center);
    ~Object();
    void Update(unsigned int dt,bool rotation,bool translation, int pause,glm::mat4 center,float scale);
    void Render();

    glm::mat4 GetModel();
    glm::mat4 GetLocation();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;
    

    float angle;
	float angleT;
	float angleR;
	float rateT;
	float rateR;
    glm::mat4 centerOfOrbit;
    glm::mat4 location;

    struct Vertex v{{0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}};
    
};

#endif /* OBJECT_H */
