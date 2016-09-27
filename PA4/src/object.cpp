#include "object.h"
#include <iostream>
#include <fstream>

Object::Object(glm::mat4 center)
{  
  /*
    # Blender File for my object. Added for trouble shooting
    o Cube
	v 2.132345 -1.000000 -0.297700
	v 2.132345 -1.000000 1.000000
	v -1.000000 -1.000000 1.000000
	v -1.000000 -1.000000 -0.297700
	v 2.132346 -0.579089 -0.297700
	v 2.132344 -0.579089 1.000001
	v -1.000000 -0.579089 1.000000
	v -1.000000 -0.579089 -0.297700
    s off
	f 5 2 1
	f 6 3 2
	f 7 4 3
	f 1 8 5
	f 5 6 2
	f 6 7 3
	f 7 8 4
	f 1 4 8
	f 2 4 1
	f 2 3 4
  */


FILE * file = fopen("../test.obj","rb");


while( 1 ){

    char lineHeader[128];

    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break;

    if ( strcmp( lineHeader, "v" ) == 0 ){
 
    glm::vec3 vertex;
    fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
    v.vertex=vertex;
    std::cout<<v.vertex.x<<" "<<v.vertex.y<<" "<<v.vertex.z<<std::endl;
    v.color = glm::vec3 {1,1,1};
    Vertices.push_back(v);
}

    else if ( strcmp( lineHeader, "f" ) == 0 ){
    std::string vertex1, vertex2, vertex3;
    unsigned int vertexIndex[3]={0,0,0};
    unsigned int dummy[3]={0,0,0};
    char test;
    fscanf(file, "%d%c ", &vertexIndex[0],&test);
   
    

    if(test == '/')
    {
      std::cout<<"switch"<<" "<<test<<std::endl;
      fscanf(file, "/%d %d//%d %d//%d \n",&dummy[0], &vertexIndex[1],&dummy[1],&vertexIndex[2],&dummy[2]);
    }

    else
    {
      std::cout<<"s"<<std::endl;
      fscanf(file, " %d %d \n", &vertexIndex[1],&vertexIndex[2]);
    }
    std::cout<<vertexIndex[0]<<" "<<vertexIndex[1]<<" "<<vertexIndex[2]<<std::endl;
    Indices.push_back(vertexIndex[0]);
    Indices.push_back(vertexIndex[1]);
    Indices.push_back(vertexIndex[2]);
}
}




/*
  Vertices = {
    {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
    {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
    {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
    {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
    {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
    {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
    {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
  };*/
/*
  Indices = {
    2, 3, 4,
    8, 7, 6,
    1, 5, 6,
    2, 6, 7,
    7, 8, 4,
    1, 4, 8,
    1, 2, 4,
    5, 8, 6,
    2, 1, 6,
    3, 2, 7,
    3, 7, 4,
    5, 1, 8
  };

  Indices = {
	5, 2, 1,
	6, 3, 2,
	7, 4, 3,
	1, 8, 5,
	5, 6, 2,
	6, 7, 3,
	7, 8, 4,
	1, 4, 8,
	2, 4, 1,
	2, 3, 4
  };*/

  // The index works at a 0th index
  for(unsigned int i = 0; i < Indices.size(); i++)
  {
    Indices[i] = Indices[i] - 1;
  }

  angle = 0.0f;

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  centerOfOrbit = center;
  location= glm::mat4(1.0f);

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt,bool rotation,bool translation, int pause,glm::mat4 center,float scale)
{/*
  angle += dt * M_PI/1000;

  switch(pause)
  {
    case 0:
	  rateR=rateT=M_PI/1000;
	  break;
	case 1:
	  rateR=rateT=0;
	  break;
	case 2:
        rateT = M_PI/1000;
	  break;
	case 3:
        rateT = 0;
	  break;
	case 4:
		rateR = M_PI/1000;
	  break;
	case 5:
		rateR = 0;
	  break;
  }

  if(rotation)
  {
    angleR += dt * rateR;
  }
  else if(!rotation)
  {
    angleR -= dt * rateR;
  }

  glm::mat4 rot= glm::rotate(glm::mat4(1.0f), (angleR), glm::vec3(0.0, 1.0, 0.0));

  if(translation)
  {
    angleT += dt * rateT;
  }
  else if(!translation)
  {
    angleT -= dt * rateT;
  }

  glm::vec3 circle(5.0f * cos(angleT), 1.0f, 5.0f * sin(angleT));



  glm::mat4 trans= glm::translate(center,circle);

  location = trans;

  trans = glm::scale(trans,glm::vec3(scale,scale,scale));
  model= trans*rot;*/
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

glm::mat4 Object::GetLocation()
{
  return location;
}
