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
    bool Initialize(int width, int height);
    void Update(unsigned int dt,float LR,float UD);
    void Render();
    void moveBox(int direction);
    void leftPaddle();
    void rightPaddle();
    void reset();
	//bool canJump;

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

    Object *m_level1;
    btCollisionShape *level1;
    btDefaultMotionState *level1MotionState = NULL;
    btRigidBody *level1RigidBody;

    Object *m_level2;
    btCollisionShape *level2;
    btDefaultMotionState *level2MotionState = NULL;
    btRigidBody *level2RigidBody;

    Object *m_level3;
    btCollisionShape *level3;
    btDefaultMotionState *level3MotionState = NULL;
    btRigidBody *level3RigidBody;

    Object *m_level4;
    btCollisionShape *level4;
    btDefaultMotionState *level4MotionState = NULL;
    btRigidBody *level4RigidBody;

    Object *m_level5;
    btCollisionShape *level5;
    btDefaultMotionState *level5MotionState = NULL;
    btRigidBody *level5RigidBody;

    Object *m_level6;
    btCollisionShape *level6;
    btDefaultMotionState *level6MotionState = NULL;
    btRigidBody *level6RigidBody;

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

    Object *m_endGoal;
    btCollisionShape *endGoal;
    btDefaultMotionState *endGoalMotionState = NULL;
    btRigidBody *endGoalRigidBody;

    Object *m_endGoal1;
    btCollisionShape *endGoal1;
    btDefaultMotionState *endGoal1MotionState = NULL;
    btRigidBody *endGoal1RigidBody;

    Object *m_endGoal2;
    btCollisionShape *endGoal2;
    btDefaultMotionState *endGoal2MotionState = NULL;
    btRigidBody *endGoal2RigidBody;

    Object *m_endGoal3;
    btCollisionShape *endGoal3;
    btDefaultMotionState *endGoal3MotionState = NULL;
    btRigidBody *endGoal3RigidBody;

    Object *m_endGoal4;
    btCollisionShape *endGoal4;
    btDefaultMotionState *endGoal4MotionState = NULL;
    btRigidBody *endGoal4RigidBody;

    Object *m_endGoal5;
    btCollisionShape *endGoal5;
    btDefaultMotionState *endGoal5MotionState = NULL;
    btRigidBody *endGoal5RigidBody;

    btCollisionShape *loss;
    btDefaultMotionState *lossMotionState = NULL;
    btRigidBody *lossRigidBody;

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
