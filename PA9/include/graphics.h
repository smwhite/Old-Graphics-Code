#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"
#include <btBulletDynamicsCommon.h>

class Graphics
{
  public:
    Graphics(string vFile, string fFile, string mFile);
    ~Graphics();
    bool Initialize(int width, int height);
    void Update(unsigned int dt);
    void Render();
    void moveBox(int direction);

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
	GLint m_gSampler;

    //Object *m_sun;
	//Object *m_mercury;
    //Object *m_venus;
    //Object *m_earth;
	//Object *m_mars;
    //Object *m_jupiter;
	//Object *m_saturn;
    //Object *m_uranus;
	//Object *m_neptune;
    //Object *m_pluto;

    //Object *m_eMoon;
    //Object *m_mMoon;
    //Object *m_jMoon;
    //Object *m_nMoon;
    //Object *m_sRing;
    //Object *m_uRing;

    Object *m_ball;
	Object *m_cube;
    Object *m_cylinder;
	Object *m_walls;

    glm::mat4 c;

    string vertexFile;
    string fragmentFile;
    string modelFile;

    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld;

    btCollisionShape *ball;
    btCollisionShape *cube;
    btCollisionShape *cylinder;
    btCollisionShape *walls;
    
    btDefaultMotionState *ballMotionState = NULL;
    btDefaultMotionState *cubeMotionState = NULL;
    btDefaultMotionState *cylinderMotionState = NULL;
    btDefaultMotionState *wallMotionState = NULL;

    btRigidBody *ballRigidBody;
    btRigidBody *cubeRigidBody;
    btRigidBody *cylinderRigidBody;
    btRigidBody *wallRigidBody;
};

#endif /* GRAPHICS_H */
