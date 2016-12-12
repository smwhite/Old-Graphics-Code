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
    friend bool bumperCallback(btManifoldPoint& cp, btCollisionObject* obj1, int id1, int index1, btCollisionObject* obj2, int id2, int index2);
    //bool lossCallback(btManifoldPoint& cp, btCollisionObject* obj1, int id1, int index1, btCollisionObject* obj2, int id2, int index2);
    bool Initialize(int width, int height);
    void Update(unsigned int dt,float LR,float UD);
    void Render();
    void moveBox(int direction);
    void leftPaddle();
    void rightPaddle();
    void reset();
    void deleteObj(btCollisionObject* obj);
	bool canJump;

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;
	GLint m_gSampler;

   glm::vec4 amb = {0.6,0.6,0.6,0.0};
    GLint m_ModelView;
    GLint m_LightPosition;
    GLint m_Projection;
	GLint m_Shininess;
	GLint m_AmbientProduct;
    GLint m_DiffuseProduct;
    GLint m_SpecularProduct;



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

    Object *m_cube;
    btCollisionShape *cube;
    btDefaultMotionState *cubeMotionState = NULL;
    btRigidBody *cubeRigidBody;

    Object *m_collectible;
    btCollisionShape *collectible;
    btDefaultMotionState *collectibleMotionState = NULL;
    btRigidBody *collectibleRigidBody;
    //void *collectiblePtr;

    Object *m_collectible1;
    btCollisionShape *collectible1;
    btDefaultMotionState *collectible1MotionState = NULL;
    btRigidBody *collectible1RigidBody;
    //void *collectible1Ptr;

    Object *m_collectible2;
    btCollisionShape *collectible2;
    btDefaultMotionState *collectible2MotionState = NULL;
    btRigidBody *collectible2RigidBody;
    //void *collectible2Ptr;

    Object *m_collectible3;
    btCollisionShape *collectible3;
    btDefaultMotionState *collectible3MotionState = NULL;
    btRigidBody *collectible3RigidBody;
    //void *collectible3Ptr;

    Object *m_collectible4;
    btCollisionShape *collectible4;
    btDefaultMotionState *collectible4MotionState = NULL;
    btRigidBody *collectible4RigidBody;
    //void *collectible4Ptr;

    Object *m_backboard;

    btCollisionShape *cover;
    btDefaultMotionState *coverMotionState = NULL;
    btRigidBody *coverRigidBody;

    btCollisionShape *loss;
    btDefaultMotionState *lossMotionState = NULL;
    btRigidBody *lossRigidBody;

    Object *m_lPaddle1;
    btCollisionShape *lPaddle1;
    btDefaultMotionState *lPaddle1MotionState = NULL;
    btRigidBody *lPaddle1RigidBody;

    Object *m_rPaddle1;
    btCollisionShape *rPaddle1;
    btDefaultMotionState *rPaddle1MotionState = NULL;
    btRigidBody *rPaddle1RigidBody;

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
