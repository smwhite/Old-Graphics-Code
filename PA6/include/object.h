#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <Magick++.h>
#include "graphics_headers.h"

class Object
{
  public:
    Object(glm::mat4 center, std::string vFile, std::string fFile, std::string mFile);
    ~Object();
    void Update(unsigned int dt,bool rotation,bool translation, int pause,glm::mat4 center,float scale);
    void Render();

    glm::mat4 GetModel();
    glm::mat4 GetLocation();

  private:
    std::string vertexFile;
    std::string fragmentFile;
    std::string modelFile;
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    GLuint m_texObj;
    //GLenum m_texTarget;
    
    Magick::Image m_image;
    Magick::Blob m_blob;

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
