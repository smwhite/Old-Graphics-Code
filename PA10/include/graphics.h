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
    void Update(unsigned int dt, glm::vec4 a,float LR,float UD);
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

    GLint m_ModelView;
    GLint m_LightPosition;
    GLint m_Projection;
	GLint m_Shininess;
	GLint m_AmbientProduct;
    GLint m_DiffuseProduct;
    GLint m_SpecularProduct;

    glm::vec4 amb = {0.6,0.6,0.6,0.0};



   GLfloat *mat_specular;
   GLfloat *mat_shininess;
   GLfloat *mat_ambient;
   GLfloat *mat_diffuse;
   GLfloat *light_position;
   GLfloat *lightmode;
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
    Object *m_cylinder1;
    Object *m_cylinder2;
	Object *m_walls;
    Object *m_lPaddle;
    Object *m_rPaddle;
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
    btCollisionShape *cylinder1;
    btCollisionShape *cylinder2;
    btCollisionShape *walls;
    btCollisionShape *lPaddle;
    btCollisionShape *rPaddle;
    
    btDefaultMotionState *ballMotionState = NULL;
    btDefaultMotionState *cubeMotionState = NULL;
    btDefaultMotionState *cylinderMotionState = NULL;
    btDefaultMotionState *cylinder1MotionState = NULL;
    btDefaultMotionState *cylinder2MotionState = NULL;
    btDefaultMotionState *wallMotionState = NULL;
    btDefaultMotionState *lPaddleMotionState = NULL;
    btDefaultMotionState *rPaddleMotionState = NULL;

    btRigidBody *ballRigidBody;
    btRigidBody *cubeRigidBody;
    btRigidBody *cylinderRigidBody;
    btRigidBody *cylinder1RigidBody;
    btRigidBody *cylinder2RigidBody;
    btRigidBody *wallRigidBody;
    btRigidBody *lPaddleRigidBody;
    btRigidBody *rPaddleRigidBody;
};

#endif /* GRAPHICS_H */
