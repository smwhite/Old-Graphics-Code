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
    void Update(unsigned int dt,float LR,float UD);
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

    Object *m_ball;
    btCollisionShape *ball;
    btDefaultMotionState *ballMotionState = NULL;
    btRigidBody *ballRigidBody;

    Object *m_walls;
    btCollisionShape *walls;
    btDefaultMotionState *wallMotionState = NULL;
    btRigidBody *wallRigidBody;

    Object *m_cylinder;
    btCollisionShape *cylinder;
    btDefaultMotionState *cylinderMotionState = NULL;
    btRigidBody *cylinderRigidBody;

    Object *m_cylinder1;
    btCollisionShape *cylinder1;  
    btDefaultMotionState *cylinder1MotionState = NULL;  
    btRigidBody *cylinder1RigidBody;

    Object *m_cylinder2;
    btCollisionShape *cylinder2;
    btDefaultMotionState *cylinder2MotionState = NULL;
    btRigidBody *cylinder2RigidBody;

    glm::mat4 c;

    string vertexFile;
    string fragmentFile;
    string modelFile;

    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher *dispatcher;
    btSequentialImpulseConstraintSolver *solver;
    btDiscreteDynamicsWorld *dynamicsWorld;
};

#endif /* GRAPHICS_H */
