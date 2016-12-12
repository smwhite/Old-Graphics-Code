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
	bool bcube0;
	bool bcube1;
	bool bcube2;
	bool bcube3;
	bool bcube4;
	bool bcube5;
	bool bcube6;

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

    Object *m_level6j;
    btCollisionShape *level6j;
    btDefaultMotionState *level6jMotionState = NULL;
    btRigidBody *level6jRigidBody;

    Object *m_level6d;
    btCollisionShape *level6d;
    btDefaultMotionState *level6dMotionState = NULL;
    btRigidBody *level6dRigidBody;

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

    Object *m_cylinder3;
    btCollisionShape *cylinder3;
    btDefaultMotionState *cylinder3MotionState = NULL;
    btRigidBody *cylinder3RigidBody;

    Object *m_cylinder4;
    btCollisionShape *cylinder4;  
    btDefaultMotionState *cylinder4MotionState = NULL;  
    btRigidBody *cylinder4RigidBody;

    Object *m_cylinder5;
    btCollisionShape *cylinder5;
    btDefaultMotionState *cylinder5MotionState = NULL;
    btRigidBody *cylinder5RigidBody;

    Object *m_cylinder6;
    btCollisionShape *cylinder6;
    btDefaultMotionState *cylinder6MotionState = NULL;
    btRigidBody *cylinder6RigidBody;

    Object *m_cylinder7;
    btCollisionShape *cylinder7;  
    btDefaultMotionState *cylinder7MotionState = NULL;  
    btRigidBody *cylinder7RigidBody;

    Object *m_cylinder8;
    btCollisionShape *cylinder8;
    btDefaultMotionState *cylinder8MotionState = NULL;
    btRigidBody *cylinder8RigidBody;

    Object *m_cylinder9;
    btCollisionShape *cylinder9;
    btDefaultMotionState *cylinder9MotionState = NULL;
    btRigidBody *cylinder9RigidBody;

    Object *m_cylinder10;
    btCollisionShape *cylinder10;  
    btDefaultMotionState *cylinder10MotionState = NULL;  
    btRigidBody *cylinder10RigidBody;

    Object *m_cylinder11;
    btCollisionShape *cylinder11;
    btDefaultMotionState *cylinder11MotionState = NULL;
    btRigidBody *cylinder11RigidBody;

    Object *m_cylinder12;
    btCollisionShape *cylinder12;
    btDefaultMotionState *cylinder12MotionState = NULL;
    btRigidBody *cylinder12RigidBody;

    Object *m_cylinder13;
    btCollisionShape *cylinder13;
    btDefaultMotionState *cylinder13MotionState = NULL;
    btRigidBody *cylinder13RigidBody;

    Object *m_cylinder14;
    btCollisionShape *cylinder14;
    btDefaultMotionState *cylinder14MotionState = NULL;
    btRigidBody *cylinder14RigidBody;

    Object *m_cylinder15;
    btCollisionShape *cylinder15;
    btDefaultMotionState *cylinder15MotionState = NULL;
    btRigidBody *cylinder15RigidBody;

    Object *m_cylinder16;
    btCollisionShape *cylinder16;
    btDefaultMotionState *cylinder16MotionState = NULL;
    btRigidBody *cylinder16RigidBody;

    Object *m_cylinder17;
    btCollisionShape *cylinder17;
    btDefaultMotionState *cylinder17MotionState = NULL;
    btRigidBody *cylinder17RigidBody;

    Object *m_cylinder18;
    btCollisionShape *cylinder18;
    btDefaultMotionState *cylinder18MotionState = NULL;
    btRigidBody *cylinder18RigidBody;

    Object *m_cylinder19;
    btCollisionShape *cylinder19;
    btDefaultMotionState *cylinder19MotionState = NULL;
    btRigidBody *cylinder19RigidBody;

    Object *m_cube;
    btCollisionShape *cube;
    btDefaultMotionState *cubeMotionState = NULL;
    btRigidBody *cubeRigidBody;

    Object *m_cube1;
    btCollisionShape *cube1;
    btDefaultMotionState *cube1MotionState = NULL;
    btRigidBody *cube1RigidBody;

    Object *m_cube2;
    btCollisionShape *cube2;
    btDefaultMotionState *cube2MotionState = NULL;
    btRigidBody *cube2RigidBody;

    Object *m_cube3;
    btCollisionShape *cube3;
    btDefaultMotionState *cube3MotionState = NULL;
    btRigidBody *cube3RigidBody;

    Object *m_cube4;
    btCollisionShape *cube4;
    btDefaultMotionState *cube4MotionState = NULL;
    btRigidBody *cube4RigidBody;

    Object *m_cube5;
    btCollisionShape *cube5;
    btDefaultMotionState *cube5MotionState = NULL;
    btRigidBody *cube5RigidBody;

    Object *m_cube6;
    btCollisionShape *cube6;
    btDefaultMotionState *cube6MotionState = NULL;
    btRigidBody *cube6RigidBody;

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
