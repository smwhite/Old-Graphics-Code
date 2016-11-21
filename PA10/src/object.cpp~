#include "object.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/color4.h>
#include <Magick++.h>

using namespace Magick;

Object::Object(glm::mat4 center,float orbitSize, int orbitSpeed, int rotationSpeed, std::string vFile, std::string fFile, std::string mFile)
{  
  vertexFile = vFile;
  fragmentFile = fFile;
  modelFile = mFile;
  


  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(modelFile, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs 
                                       | aiProcess_JoinIdenticalVertices);

  aiMesh* mesh = scene->mMeshes[0];

  for(unsigned int i=0;i< mesh->mNumVertices;i++)
  {
    const aiVector3D* pos = &(mesh->mVertices[i]);
    const aiVector3D* uv = &(mesh->mTextureCoords[0][i]);

    v.vertex = glm::vec3 {pos->x,pos->y,pos->z};
	v.uv = glm::vec2{uv->x,uv->y};
    Vertices.push_back(v);
  }



  for(unsigned int i=0;i<mesh->mNumFaces;i++)
  {
    const aiFace& face = mesh->mFaces[i];
    assert(face.mNumIndices ==3);

    Indices.push_back(face.mIndices[0]);
    Indices.push_back(face.mIndices[1]);
    Indices.push_back(face.mIndices[2]);    
  }

  aiString mat;
  scene->mMaterials[1]->GetTexture(aiTextureType_DIFFUSE,0,&mat);
  std::string matFile = mat.C_Str();
  std::string m_fileName = "../models/"+matFile;
  m_image.read(m_fileName);
  m_image.write(&m_blob, "RGBA");

  angle = 0.0f;



  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //glActiveTexture(GL_TEXTURE0);
  //glBindTexture(GL_TEXTURE_2D, m_texObj);

  //glBindTexture(GL_TEXTURE_2D, 0);  


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  centerOfOrbit = center;
  orbSize = orbitSize;
  orbSpeed = orbitSpeed;
  rotSpeed = rotationSpeed;
  location= glm::mat4(1.0f);

}

Object::~Object()
{
  Vertices.clear();
  Indices.clear();
}

void Object::Update(unsigned int dt,bool rotation,bool translation, int pause,glm::mat4 center,float scale, float multiplier)
{
  angle += dt * M_PI/1000;

  rateR=M_PI/rotSpeed * multiplier;
  rateT=M_PI/orbSpeed * multiplier;

  angleR += dt * rateR;


  glm::mat4 rot= glm::rotate(glm::mat4(1.0f), (angleR), glm::vec3(0.0, 1.0, 0.0));


  angleT += dt * rateT;


  glm::vec3 circle(orbSize * cos(angleT), 0.0f, orbSize * sin(angleT));
  glm::mat4 trans= glm::translate(center,circle);

  if(orbSize != 0.0)
  {
    location = trans;

    trans = glm::scale(trans,glm::vec3(scale,scale,scale));
    model= trans*rot;
  }

  else
  {
   location = trans;
   rot = glm::scale(rot,glm::vec3(scale,scale,scale));
   model= rot;
  }
}

glm::mat4 Object::GetModel()
{
  return model;
}

void Object::Render()
{
  glGenTextures(1, &m_texObj);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.columns(), m_image.rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
  glBindTexture(GL_TEXTURE_2D, m_texObj);


  glDeleteTextures(1, &m_texObj);


  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,uv));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

  glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
}

glm::mat4 Object::GetLocation()
{
  return location;
}
