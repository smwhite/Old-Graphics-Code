#include "graphics.h"
#include <btBulletDynamicsCommon.h>
#include <iostream>

int score = 0;
int numBalls = 3;
bool gameOver = false;
bool lostBall = false;
void *endGoalPtr;
void *endGoal1Ptr;
void *endGoal2Ptr;
void *endGoal3Ptr;
void *endGoal4Ptr;
void *endGoal5Ptr;

void *level1Ptr;
void *level2Ptr;
void *level3Ptr;
void *level4Ptr;
void *level5Ptr;
void *level6jPtr;
void *level6aPtr;
void *level6rPtr;
void *level6dPtr;

bool canJump;
bool jumping = false;
bool canMove=true;

btRigidBody *tempBallRigidBody;

bool bumperCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2)
  {
    void *temp1Ptr = obj1->getCollisionObject()->getUserPointer();

    void *temp2Ptr = obj2->getCollisionObject()->getUserPointer();

    if(std::string(obj2->getCollisionShape()->getName()) == "STATICPLANE")
    {

         gameOver = true;
		 canMove = false;
         cout << "GAME OVER" << endl; 
         std::cout << "Final score: " << score << endl; 
         std::cout << "Press R to Play Again" << endl;
        
    }

    else if(temp1Ptr == endGoalPtr || temp2Ptr == endGoalPtr)
    {
        cout << "C0" << endl;
        score ++;
        std::cout << "Score: " << score << endl;
        tempBallRigidBody->activate(true);
        tempBallRigidBody->setLinearVelocity(btVector3(0,0,0));
        tempBallRigidBody->translate(btVector3(-200, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
    }

    else if(temp1Ptr == endGoal1Ptr || temp2Ptr == endGoal1Ptr)
    {
        cout << "C1" << endl;
        score ++;
        std::cout << "Score: " << score << endl;
        tempBallRigidBody->activate(true);
        tempBallRigidBody->setLinearVelocity(btVector3(0,0,0));
        tempBallRigidBody->translate(btVector3(-450, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
    }

    else if(temp1Ptr == endGoal2Ptr || temp2Ptr == endGoal2Ptr)
    {
        cout << "C2" << endl;
        score ++;
        std::cout << "Score: " << score << endl;
        tempBallRigidBody->activate(true);
        tempBallRigidBody->translate(btVector3(-850, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
    }

    else if(temp1Ptr == endGoal3Ptr || temp2Ptr == endGoal3Ptr)
    {
        cout << "C3" << endl;
        score ++;
        std::cout << "Score: " << score << endl;
        tempBallRigidBody->activate(true);
        tempBallRigidBody->setLinearVelocity(btVector3(0,0,0));
        tempBallRigidBody->translate(btVector3(-850, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
    }

    else if(temp1Ptr == endGoal4Ptr || temp2Ptr == endGoal4Ptr)
    {
        cout << "C4" << endl;
        score ++;
        std::cout << "Score: " << score << endl;
        tempBallRigidBody->activate(true);
        tempBallRigidBody->setLinearVelocity(btVector3(0,0,0));
        tempBallRigidBody->translate(btVector3(0, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
    }

    else if(temp1Ptr == endGoal5Ptr || temp2Ptr == endGoal5Ptr)
    {
        cout << "C5" << endl;
        score ++;
        std::cout << "Score: " << score << endl;
        tempBallRigidBody->activate(true);
        tempBallRigidBody->setLinearVelocity(btVector3(0,0,0));
        tempBallRigidBody->translate(btVector3(500, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
    }

  


    //if(jumping == true)
    //{
        //jumping = false;
   // }

    return false;
  }


Graphics::Graphics(string vFile, string fFile, string mFile)
{
  vertexFile = vFile;
  fragmentFile = fFile;
  modelFile = mFile;

  broadphase = new btDbvtBroadphase();
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  solver = new btSequentialImpulseConstraintSolver;
  dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
  dynamicsWorld->setGravity(btVector3(0, 0, 0));
  gContactAddedCallback=bumperCallback;
  canJump = true;
  bcube0=true;
  bcube1=true;
  bcube2=true;
  bcube3=true;
  bcube4=true;
  bcube5=true;
  bcube6=true;
  canMove=false;
}

Graphics::~Graphics()
{
  delete dynamicsWorld;
  dynamicsWorld = NULL;

  delete solver;
  solver = NULL;

  delete dispatcher;
  dispatcher = NULL;

  delete collisionConfiguration;
  collisionConfiguration = NULL; 

  delete broadphase;
  broadphase = NULL; 
}


bool Graphics::Initialize(int width, int height)
{
  // Used for the linux OS
  #if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;

    auto status = glewInit();

    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();

    //Check for error
    if (status != GLEW_OK)
    {
      std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
      return false;
    }
  #endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if(!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

// create objects

  btTriangleMesh *objTriMesh1 = new btTriangleMesh();
  m_level1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/rectanglefloor.obj", true, objTriMesh1);
  level1 = new btBvhTriangleMeshShape(objTriMesh1, true);
  level1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo level1RigidBodyCI(0, level1MotionState, level1, btVector3(0, 0, 0));
  level1RigidBody = new btRigidBody(level1RigidBodyCI);
  level1RigidBody->setUserPointer(level1RigidBody);
  level1Ptr = level1RigidBody->getUserPointer();
  cout << level1Ptr << endl;
  dynamicsWorld->addRigidBody(level1RigidBody);
  level1RigidBody->setCollisionFlags(level1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  btTriangleMesh *objTriMesh2 = new btTriangleMesh();
  m_level2 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/anglefloor.obj", true, objTriMesh2);
  level2 = new btBvhTriangleMeshShape(objTriMesh2, true);
  level2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-203, -1, 50)));
  btRigidBody::btRigidBodyConstructionInfo level2RigidBodyCI(0, level2MotionState, level2, btVector3(0, 0, 0));
  level2RigidBody = new btRigidBody(level2RigidBodyCI);
  level2RigidBody->setUserPointer(level2RigidBody);
  level2Ptr = level2RigidBody->getUserPointer();
  cout << level2Ptr << endl;
  dynamicsWorld->addRigidBody(level2RigidBody);
  level2RigidBody->setCollisionFlags(level2RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  btTriangleMesh *objTriMesh3 = new btTriangleMesh();
  m_level3 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/jumpfloor.obj", true, objTriMesh3);
  level3 = new btBvhTriangleMeshShape(objTriMesh3, true);
  level3MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-450, -1, -25)));
  btRigidBody::btRigidBodyConstructionInfo level3RigidBodyCI(0, level3MotionState, level3, btVector3(0, 0, 0));
  level3RigidBody = new btRigidBody(level3RigidBodyCI);
  level3RigidBody->setUserPointer(level3RigidBody);
  level3Ptr = level3RigidBody->getUserPointer();
  cout << level3Ptr << endl;
  dynamicsWorld->addRigidBody(level3RigidBody);
  level3RigidBody->setCollisionFlags(level3RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  btTriangleMesh *objTriMesh4 = new btTriangleMesh();
  m_level4 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/diamondfloor.obj", true, objTriMesh4);
  level4 = new btBvhTriangleMeshShape(objTriMesh4, true);
  level4MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-650, -1, 10)));
  btRigidBody::btRigidBodyConstructionInfo level4RigidBodyCI(0, level4MotionState, level4, btVector3(0, 0, 0));
  level4RigidBody = new btRigidBody(level4RigidBodyCI);
  level4RigidBody->setUserPointer(level4RigidBody);
  level4Ptr = level4RigidBody->getUserPointer();
  cout << level4Ptr << endl;
  dynamicsWorld->addRigidBody(level4RigidBody);
  level4RigidBody->setCollisionFlags(level4RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);


  btTriangleMesh *objTriMesh5 = new btTriangleMesh();
  m_level5 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/rectanglefloor.obj", true, objTriMesh5);
  level5 = new btBvhTriangleMeshShape(objTriMesh5, true);
  level5MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-850, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo level5RigidBodyCI(0, level5MotionState, level5, btVector3(0, 0, 0));
  level5RigidBody = new btRigidBody(level5RigidBodyCI);
  level5RigidBody->setUserPointer(level5RigidBody);
  level5Ptr = level5RigidBody->getUserPointer();
  cout << level5Ptr << endl;
  dynamicsWorld->addRigidBody(level5RigidBody);
  level5RigidBody->setCollisionFlags(level5RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
//////////////////////////////////////LEVEL 6///////////////////////////////////////////////////////////////////////////////////
  btTriangleMesh *objTriMesh6 = new btTriangleMesh();
  m_level6j = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/jumpfloor.obj", true, objTriMesh6);
  level6j = new btBvhTriangleMeshShape(objTriMesh6, true);
  level6jMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(500, -1, -25)));
  btRigidBody::btRigidBodyConstructionInfo level6jRigidBodyCI(0, level6jMotionState, level6j, btVector3(0, 0, 0));
  level6jRigidBody = new btRigidBody(level6jRigidBodyCI);
  level6jRigidBody->setUserPointer(level6jRigidBody);
  level6jPtr = level6jRigidBody->getUserPointer();
  cout << level6jPtr << endl;
  dynamicsWorld->addRigidBody(level6jRigidBody);
  level6jRigidBody->setCollisionFlags(level6jRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_level6d = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/diamondfloor.obj", true, objTriMesh6);
  level6d = new btBvhTriangleMeshShape(objTriMesh6, true);
  level6dMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(500, -1, 130)));
  btRigidBody::btRigidBodyConstructionInfo level6dRigidBodyCI(0, level6dMotionState, level6d, btVector3(0, 0, 0));
  level6dRigidBody = new btRigidBody(level6dRigidBodyCI);
  level6dRigidBody->setUserPointer(level6dRigidBody);
  level6dPtr = level6dRigidBody->getUserPointer();
  cout << level6dPtr << endl;
  dynamicsWorld->addRigidBody(level6dRigidBody);
  level6dRigidBody->setCollisionFlags(level6dRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  m_ball = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/ball.obj", false, NULL);
  ball = new btSphereShape (1);
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -25)));
  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(1, ballMotionState, ball, btVector3(0, 0, 0));
  ballRigidBody = new btRigidBody(ballRigidBodyCI);
  dynamicsWorld->addRigidBody(ballRigidBody);
  ballRigidBody->setRestitution(1.0);
  ballRigidBody->setGravity(btVector3(0, -9.8, 0));
  tempBallRigidBody = ballRigidBody;

  btTriangleMesh *egTriMesh = new btTriangleMesh();
  m_endGoal = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/goal.obj", true, egTriMesh);
  endGoal = new btBvhTriangleMeshShape(egTriMesh, true);
  endGoalMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 25)));
  btRigidBody::btRigidBodyConstructionInfo endGoalRigidBodyCI(0, endGoalMotionState, endGoal, btVector3(0, 0, 0));
  endGoalRigidBody = new btRigidBody(endGoalRigidBodyCI);  
  endGoalRigidBody->setUserPointer(endGoalRigidBody);
  endGoalPtr = endGoalRigidBody->getUserPointer();
  cout << endGoalPtr << endl;
  dynamicsWorld->addRigidBody(endGoalRigidBody);
  endGoalRigidBody->setCollisionFlags(endGoalRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
  
  m_endGoal1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/goal.obj", true, egTriMesh);
  endGoal1 = new btBvhTriangleMeshShape(egTriMesh, true);
  endGoal1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-203, 0, 65)));
  btRigidBody::btRigidBodyConstructionInfo endGoal1RigidBodyCI(0, endGoal1MotionState, endGoal1, btVector3(0, 0, 0));
  endGoal1RigidBody = new btRigidBody(endGoal1RigidBodyCI);
  endGoal1RigidBody->setUserPointer(endGoal1RigidBody);
  endGoal1Ptr = endGoal1RigidBody->getUserPointer();
  cout << endGoal1Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal1RigidBody);
  endGoal1RigidBody->setCollisionFlags(endGoal1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_endGoal2 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/goal.obj", true, egTriMesh);
  endGoal2 = new btBvhTriangleMeshShape(egTriMesh, true);
  endGoal2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-450, 0, 80)));
  btRigidBody::btRigidBodyConstructionInfo endGoal2RigidBodyCI(0, endGoal2MotionState, endGoal2, btVector3(0, 0, 0));
  endGoal2RigidBody = new btRigidBody(endGoal2RigidBodyCI);
  endGoal2RigidBody->setUserPointer(endGoal2RigidBody);
  endGoal2Ptr = endGoal2RigidBody->getUserPointer();
  cout << endGoal2Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal2RigidBody);
  endGoal2RigidBody->setCollisionFlags(endGoal2RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_endGoal3 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/goal.obj", true, egTriMesh);
  endGoal3 = new btBvhTriangleMeshShape(egTriMesh, true);
  endGoal3MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-850, 0, 25)));
  btRigidBody::btRigidBodyConstructionInfo endGoal3RigidBodyCI(0, endGoal3MotionState, endGoal3, btVector3(0, 0, 0));
  endGoal3RigidBody = new btRigidBody(endGoal3RigidBodyCI);
  endGoal3RigidBody->setUserPointer(endGoal3RigidBody);
  endGoal3Ptr = endGoal3RigidBody->getUserPointer();
  cout << endGoal3Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal3RigidBody);
  endGoal3RigidBody->setCollisionFlags(endGoal3RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_endGoal4 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/goal.obj", true, egTriMesh);
  endGoal4 = new btBvhTriangleMeshShape(egTriMesh, true);
  endGoal4MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, 0, -5)));
  btRigidBody::btRigidBodyConstructionInfo endGoal4RigidBodyCI(0, endGoal4MotionState, endGoal4, btVector3(0, 0, 0));
  endGoal4RigidBody = new btRigidBody(endGoal4RigidBodyCI);
  endGoal4RigidBody->setUserPointer(endGoal4RigidBody);
  endGoal4Ptr = endGoal4RigidBody->getUserPointer();
  cout << endGoal4Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal4RigidBody);  
  endGoal4RigidBody->setCollisionFlags(endGoal4RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_endGoal5 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/goal.obj", true, egTriMesh);
  endGoal5 = new btBvhTriangleMeshShape(egTriMesh, true);
  endGoal5MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, 0, 8)));
  btRigidBody::btRigidBodyConstructionInfo endGoal5RigidBodyCI(0, endGoal5MotionState, endGoal5, btVector3(0, 0, 0));
  endGoal5RigidBody = new btRigidBody(endGoal5RigidBodyCI);
  endGoal5RigidBody->setUserPointer(endGoal5RigidBody);
  endGoal5Ptr = endGoal5RigidBody->getUserPointer();
  cout << endGoal5Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal5RigidBody);  
  endGoal5RigidBody->setCollisionFlags(endGoal5RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

//////////LEVEL 2 BUMPERS////////////////////////////////////////////////////////////////////
  m_cylinder = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder = new btCylinderShape(btVector3(1, 10, 1));
  cylinderMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-630, -1, -5)));
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMotionState, cylinder, btVector3(0, 0, 0));
  cylinderRigidBody = new btRigidBody(cylinderRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinderRigidBody);
  cylinderRigidBody->setRestitution(1.0);
  cylinderRigidBody->setCollisionFlags(cylinderRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder1 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-235, -1, 20)));
  btRigidBody::btRigidBodyConstructionInfo cylinder1RigidBodyCI(0, cylinder1MotionState, cylinder1, btVector3(0, 0, 0));
  cylinder1RigidBody = new btRigidBody(cylinder1RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder1RigidBody);
  cylinder1RigidBody->setRestitution(1.0);
  cylinder1RigidBody->setCollisionFlags(cylinder1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder2 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder2 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-245, -1, 20)));
  btRigidBody::btRigidBodyConstructionInfo cylinder2RigidBodyCI(0, cylinder2MotionState, cylinder2, btVector3(0, 0, 0));
  cylinder2RigidBody = new btRigidBody(cylinder2RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder2RigidBody);
  cylinder2RigidBody->setRestitution(1.0);
  cylinder2RigidBody->setCollisionFlags(cylinder2RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder3 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder3 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder3MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-240, -1, 25)));
  btRigidBody::btRigidBodyConstructionInfo cylinder3RigidBodyCI(0, cylinder3MotionState, cylinder3, btVector3(0, 0, 0));
  cylinder3RigidBody = new btRigidBody(cylinder3RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder3RigidBody);
  cylinder3RigidBody->setRestitution(1.0);
  cylinder3RigidBody->setCollisionFlags(cylinder3RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder4 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder4 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder4MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-235, -1, 30)));
  btRigidBody::btRigidBodyConstructionInfo cylinder4RigidBodyCI(0, cylinder4MotionState, cylinder4, btVector3(0, 0, 0));
  cylinder4RigidBody = new btRigidBody(cylinder4RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder4RigidBody);
  cylinder4RigidBody->setRestitution(1.0);
  cylinder4RigidBody->setCollisionFlags(cylinder4RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder5 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder5 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder5MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-245, -1, 30)));
  btRigidBody::btRigidBodyConstructionInfo cylinder5RigidBodyCI(0, cylinder5MotionState, cylinder5, btVector3(0, 0, 0));
  cylinder5RigidBody = new btRigidBody(cylinder5RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder5RigidBody);
  cylinder5RigidBody->setRestitution(1.0);
  cylinder5RigidBody->setCollisionFlags(cylinder5RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder6 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder6 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder6MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-240, -1, 35)));
  btRigidBody::btRigidBodyConstructionInfo cylinder6RigidBodyCI(0, cylinder6MotionState, cylinder6, btVector3(0, 0, 0));
  cylinder6RigidBody = new btRigidBody(cylinder6RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder6RigidBody);
  cylinder6RigidBody->setRestitution(1.0);
  cylinder6RigidBody->setCollisionFlags(cylinder6RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder7 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder7 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder7MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-240, -1, 15)));
  btRigidBody::btRigidBodyConstructionInfo cylinder7RigidBodyCI(0, cylinder7MotionState, cylinder7, btVector3(0, 0, 0));
  cylinder7RigidBody = new btRigidBody(cylinder7RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder7RigidBody);
  cylinder7RigidBody->setRestitution(1.0);
  cylinder7RigidBody->setCollisionFlags(cylinder7RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
//////////LEVEL 2 BUMPERS////////////////////////////////////////////////////////////////////
  m_cylinder8 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder8 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder8MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-12, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder8RigidBodyCI(0, cylinder8MotionState, cylinder8, btVector3(0, 0, 0));
  cylinder8RigidBody = new btRigidBody(cylinder8RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder8RigidBody);
  cylinder8RigidBody->setRestitution(1.0);
  cylinder8RigidBody->setCollisionFlags(cylinder8RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder9 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder9 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder9MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-18, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder9RigidBodyCI(0, cylinder9MotionState, cylinder9, btVector3(0, 0, 0));
  cylinder9RigidBody = new btRigidBody(cylinder9RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder9RigidBody);
  cylinder9RigidBody->setRestitution(1.0);
  cylinder9RigidBody->setCollisionFlags(cylinder9RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder10 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder10 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder10MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-24, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder10RigidBodyCI(0, cylinder10MotionState, cylinder10, btVector3(0, 0, 0));
  cylinder10RigidBody = new btRigidBody(cylinder10RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder10RigidBody);
  cylinder10RigidBody->setRestitution(1.0);
  cylinder10RigidBody->setCollisionFlags(cylinder10RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder11 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder11 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder11MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-30, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder11RigidBodyCI(0, cylinder11MotionState, cylinder11, btVector3(0, 0, 0));
  cylinder11RigidBody = new btRigidBody(cylinder11RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder11RigidBody);
  cylinder11RigidBody->setRestitution(1.0);
  cylinder11RigidBody->setCollisionFlags(cylinder11RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder12 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder12 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder12MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-36, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder12RigidBodyCI(0, cylinder12MotionState, cylinder12, btVector3(0, 0, 0));
  cylinder12RigidBody = new btRigidBody(cylinder12RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder12RigidBody);
  cylinder12RigidBody->setRestitution(1.0);
  cylinder12RigidBody->setCollisionFlags(cylinder12RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder13 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder13 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder13MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-42, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder13RigidBodyCI(0, cylinder13MotionState, cylinder13, btVector3(0, 0, 0));
  cylinder13RigidBody = new btRigidBody(cylinder13RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder13RigidBody);
  cylinder13RigidBody->setRestitution(1.0);
  cylinder13RigidBody->setCollisionFlags(cylinder13RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder14 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder14 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder14MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-48, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder14RigidBodyCI(0, cylinder14MotionState, cylinder14, btVector3(0, 0, 0));
  cylinder14RigidBody = new btRigidBody(cylinder14RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder14RigidBody);
  cylinder14RigidBody->setRestitution(1.0);
  cylinder14RigidBody->setCollisionFlags(cylinder14RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder15 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder15 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder15MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-54, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder15RigidBodyCI(0, cylinder15MotionState, cylinder15, btVector3(0, 0, 0));
  cylinder15RigidBody = new btRigidBody(cylinder15RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder15RigidBody);
  cylinder15RigidBody->setRestitution(1.0);
  cylinder15RigidBody->setCollisionFlags(cylinder15RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder16 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder16 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder16MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-60, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder16RigidBodyCI(0, cylinder16MotionState, cylinder16, btVector3(0, 0, 0));
  cylinder16RigidBody = new btRigidBody(cylinder16RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder16RigidBody);
  cylinder16RigidBody->setRestitution(1.0);
  cylinder16RigidBody->setCollisionFlags(cylinder16RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder17 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder17 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder17MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-66, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder17RigidBodyCI(0, cylinder17MotionState, cylinder17, btVector3(0, 0, 0));
  cylinder17RigidBody = new btRigidBody(cylinder17RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder17RigidBody);
  cylinder17RigidBody->setRestitution(1.0);
  cylinder17RigidBody->setCollisionFlags(cylinder17RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder18 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder18 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder18MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-72, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder18RigidBodyCI(0, cylinder18MotionState, cylinder18, btVector3(0, 0, 0));
  cylinder18RigidBody = new btRigidBody(cylinder18RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder18RigidBody);
  cylinder18RigidBody->setRestitution(1.0);
  cylinder18RigidBody->setCollisionFlags(cylinder18RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder19 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/caution.obj", false, NULL);
  cylinder19 = new btCylinderShape(btVector3(1, 10, 1));
  cylinder19MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-78, -1, 80)));
  btRigidBody::btRigidBodyConstructionInfo cylinder19RigidBodyCI(0, cylinder19MotionState, cylinder19, btVector3(0, 0, 0));
  cylinder19RigidBody = new btRigidBody(cylinder19RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder19RigidBody);
  cylinder19RigidBody->setRestitution(1.0);
  cylinder19RigidBody->setCollisionFlags(cylinder19RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

//LEVEL 5 MOVING METAL CUBES///////////////////////////////////////////////////////////////////////////////////
  m_cube = new Object(vertexFile, fragmentFile, "../models/metalbox.obj", false, NULL);
  cube = new btBoxShape (btVector3(3.5, 3.5, 3.5));
  cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-838, 3, 8)));
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(1, cubeMotionState, cube, btVector3(0, 0, 0));
  cubeRigidBody = new btRigidBody(cubeRigidBodyCI);
  cubeRigidBody->setRestitution(1.0);
  dynamicsWorld->addRigidBody(cubeRigidBody);

  m_cube1 = new Object(vertexFile, fragmentFile, "../models/metalbox.obj", false, NULL);
  cube1 = new btBoxShape (btVector3(3.5, 3.5, 3.5));
  cube1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-862, 3, -2)));
  btRigidBody::btRigidBodyConstructionInfo cube1RigidBodyCI(1, cube1MotionState, cube1, btVector3(0, 0, 0));
  cube1RigidBody = new btRigidBody(cube1RigidBodyCI);
  cube1RigidBody->setRestitution(1.0);
  dynamicsWorld->addRigidBody(cube1RigidBody);

  m_cube2 = new Object(vertexFile, fragmentFile, "../models/metalbox.obj", false, NULL);
  cube2 = new btBoxShape (btVector3(3.5, 3.5, 3.5));
  cube2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-838, 3, -12)));
  btRigidBody::btRigidBodyConstructionInfo cube2RigidBodyCI(1, cube2MotionState, cube2, btVector3(0, 0, 0));
  cube2RigidBody = new btRigidBody(cube2RigidBodyCI);
  cube2RigidBody->setRestitution(1.0);
  dynamicsWorld->addRigidBody(cube2RigidBody);

  m_cube3 = new Object(vertexFile, fragmentFile, "../models/metalbox.obj", false, NULL);
  cube3 = new btBoxShape (btVector3(3.5, 3.5, 3.5));
  cube3MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(450, 3, 130)));
  btRigidBody::btRigidBodyConstructionInfo cube3RigidBodyCI(1, cube3MotionState, cube3, btVector3(0, 0, 0));
  cube3RigidBody = new btRigidBody(cube3RigidBodyCI);
  cube3RigidBody->setRestitution(1.0);
  dynamicsWorld->addRigidBody(cube3RigidBody);

  m_cube4 = new Object(vertexFile, fragmentFile, "../models/metalbox.obj", false, NULL);
  cube4 = new btBoxShape (btVector3(3.5, 3.5, 3.5));
  cube4MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(550, 3, 130)));
  btRigidBody::btRigidBodyConstructionInfo cube4RigidBodyCI(1, cube4MotionState, cube4, btVector3(0, 0, 0));
  cube4RigidBody = new btRigidBody(cube4RigidBodyCI);
  cube4RigidBody->setRestitution(1.0);
  dynamicsWorld->addRigidBody(cube4RigidBody);

  m_cube5 = new Object(vertexFile, fragmentFile, "../models/metalbox.obj", false, NULL);
  cube5 = new btBoxShape (btVector3(3.5, 3.5, 3.5));
  cube5MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(520, 3, 50)));
  btRigidBody::btRigidBodyConstructionInfo cube5RigidBodyCI(1, cube5MotionState, cube5, btVector3(0, 0, 0));
  cube5RigidBody = new btRigidBody(cube5RigidBodyCI);
  cube5RigidBody->setRestitution(1.0);
  dynamicsWorld->addRigidBody(cube5RigidBody);

  m_cube6 = new Object(vertexFile, fragmentFile, "../models/metalbox.obj", false, NULL);
  cube6 = new btBoxShape (btVector3(3.5, 3.5, 3.5));
  cube6MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(520, 3, 0)));
  btRigidBody::btRigidBodyConstructionInfo cube6RigidBodyCI(1, cube6MotionState, cube6, btVector3(0, 0, 0));
  cube6RigidBody = new btRigidBody(cube6RigidBodyCI);
  cube6RigidBody->setRestitution(1.0);
  dynamicsWorld->addRigidBody(cube6RigidBody);
//LEVEL 5 MOVING METAL CUBES///////////////////////////////////////////////////////////////////////////////////

  loss = new btStaticPlaneShape (btVector3(0, 1, 0), 1);
  lossMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -10, 0)));
  btRigidBody::btRigidBodyConstructionInfo lossRigidBodyCI(0, lossMotionState, loss, btVector3(0, 0, 0));
  lossRigidBody = new btRigidBody(lossRigidBodyCI);
  dynamicsWorld->addRigidBody(lossRigidBody);
  lossRigidBody->setCollisionFlags(cylinder1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
  
  // Set up the shaders
  m_shader = new Shader("../shaders/vertexFL.vert", "../shaders/fragmentFL.frag");
  if(!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if(!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if(!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if(!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_modelMatrix not found\n");
    return false;
  }
  // Locate the model texture in the shader
  m_gSampler = m_shader->GetUniformLocation("gSampler");
  if (m_gSampler == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_gSampler not found\n");
    return false;
  } 

  // Locate the ModelView
  m_ModelView = m_shader->GetUniformLocation("ModelView");
  if (m_ModelView == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_ModelView not found\n");
    return false;
  } 
  // Locate the LightPosition
  m_LightPosition = m_shader->GetUniformLocation("LightPosition");
  if (m_LightPosition == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_LightPosition not found\n");
    return false;
  } 
  // Locate the Projection
  m_Projection = m_shader->GetUniformLocation("Projection");
  if (m_Projection == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_Projection not found\n");
    return false;
  } 

  // Locate the Shininess
  m_Shininess = m_shader->GetUniformLocation("Shininess");
  if (m_Shininess == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_Shininess not found\n");
    return false;
  } 

  // Locate the AmbientProduct
  m_AmbientProduct = m_shader->GetUniformLocation("AmbientProduct");
  if (m_AmbientProduct == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_AmbientProduct not found\n");
    return false;
  } 

  // Locate the DiffuseProduct
  m_DiffuseProduct = m_shader->GetUniformLocation("DiffuseProduct");
  if (m_DiffuseProduct == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_DiffuseProduct not found\n");
    return false;
  } 

  // Locate the SpecularProduct
  m_SpecularProduct = m_shader->GetUniformLocation("SpecularProduct");
  if (m_SpecularProduct == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_SpecularProduct not found\n");
    return false;
  }

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt,float LR,float UD)
{
  if(gameOver == false && lostBall == true)
    {
     ballRigidBody->activate(true);
     ballRigidBody->translate(btVector3(0, -1, -25)- ballRigidBody->getCenterOfMassPosition());
     ballRigidBody->setLinearVelocity(btVector3(0,0,0));
     lostBall = false;
    }

  else if(gameOver == true)
    {
     gameOver = false;
     ballRigidBody->activate(true);
     ballRigidBody->translate(btVector3(0, -1, -25)- ballRigidBody->getCenterOfMassPosition());
     ballRigidBody->setLinearVelocity(btVector3(0,0,0));
    }
  // Update the object
  btTransform trans;
  btScalar m[16];
  dynamicsWorld->stepSimulation(1/60.f, 10);

  ballRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_ball->Update(dt, glm::make_mat4(m));

  glm::mat4 test = glm::make_mat4(m);
  m_camera->Update(test[3].x,test[3].z,0.0,0.0,0.0);

  level1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_level1->Update(dt, glm::make_mat4(m));

  level2RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_level2->Update(dt, glm::make_mat4(m));

  level3RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_level3->Update(dt, glm::make_mat4(m));

  level4RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_level4->Update(dt, glm::make_mat4(m));

  level5RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_level5->Update(dt, glm::make_mat4(m));

  level6jRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_level6j->Update(dt, glm::make_mat4(m));

  level6dRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_level6d->Update(dt, glm::make_mat4(m));

  endGoalRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_endGoal->Update(dt, glm::make_mat4(m));

  endGoal1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_endGoal1->Update(dt, glm::make_mat4(m));

  endGoal2RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_endGoal2->Update(dt, glm::make_mat4(m));

  endGoal3RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_endGoal3->Update(dt, glm::make_mat4(m));

  endGoal4RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_endGoal4->Update(dt, glm::make_mat4(m));

  endGoal5RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_endGoal5->Update(dt, glm::make_mat4(m));

  cylinderRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder->Update(dt, glm::make_mat4(m));

  cylinder1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder1->Update(dt, glm::make_mat4(m));

  cylinder2RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder2->Update(dt, glm::make_mat4(m));

  cylinder3RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder3->Update(dt, glm::make_mat4(m));

  cylinder4RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder4->Update(dt, glm::make_mat4(m));

  cylinder5RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder5->Update(dt, glm::make_mat4(m));

  cylinder6RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder6->Update(dt, glm::make_mat4(m));

  cylinder7RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder7->Update(dt, glm::make_mat4(m));

  cylinder8RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder8->Update(dt, glm::make_mat4(m));

  cylinder9RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder9->Update(dt, glm::make_mat4(m));

  cylinder10RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder10->Update(dt, glm::make_mat4(m));

  cylinder11RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder11->Update(dt, glm::make_mat4(m));

  cylinder12RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder12->Update(dt, glm::make_mat4(m));

  cylinder13RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder13->Update(dt, glm::make_mat4(m));

  cylinder14RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder14->Update(dt, glm::make_mat4(m));

  cylinder15RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder15->Update(dt, glm::make_mat4(m));

  cylinder16RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder16->Update(dt, glm::make_mat4(m));

  cylinder17RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder17->Update(dt, glm::make_mat4(m));

  cylinder18RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder18->Update(dt, glm::make_mat4(m));

  cylinder19RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder19->Update(dt, glm::make_mat4(m));

//LEVEL 5 MOVING METAL CUBES///////////////////////////////////////////////////////////////////////////////////
  cubeRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cube->Update(dt, glm::make_mat4(m));

  glm::mat4 cube0 = glm::make_mat4(m);

  cube1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cube1->Update(dt, glm::make_mat4(m));

  glm::mat4 cube1 = glm::make_mat4(m);

  cube2RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cube2->Update(dt, glm::make_mat4(m));

  glm::mat4 cube2 = glm::make_mat4(m);

  cube3RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cube3->Update(dt, glm::make_mat4(m));

  glm::mat4 cube3 = glm::make_mat4(m);

  cube4RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cube4->Update(dt, glm::make_mat4(m));

  glm::mat4 cube4 = glm::make_mat4(m);

  cube5RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cube5->Update(dt, glm::make_mat4(m));

  glm::mat4 cube5 = glm::make_mat4(m);

  cube6RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cube6->Update(dt, glm::make_mat4(m));

  glm::mat4 cube6 = glm::make_mat4(m);

  if(bcube0)
  {
    cubeRigidBody->activate(true);
    cubeRigidBody->setLinearVelocity(btVector3(-10, 0, 0));
	if(cube0[3].x < -870)
	{
		bcube0 = false;

	}
  }
  if(!bcube0)
  {
    cubeRigidBody->activate(true);
    cubeRigidBody->setLinearVelocity(btVector3(10, 0, 0));
	if(cube0[3].x > -830)
	{
		bcube0 = true;
	}
  }
  if(!bcube1)
  {
    cube1RigidBody->activate(true);
    cube1RigidBody->setLinearVelocity(btVector3(-10, 0, 0));
	if(cube1[3].x < -870)
	{
		bcube1 = true;

	}
  }
  if(bcube1)
  {
    cube1RigidBody->activate(true);
    cube1RigidBody->setLinearVelocity(btVector3(10, 0, 0));
	if(cube1[3].x > -830)
	{
		bcube1 = false;
	}
  }
  if(bcube2)
  {
    cube2RigidBody->activate(true);
    cube2RigidBody->setLinearVelocity(btVector3(-10, 0, 0));
	if(cube2[3].x < -870)
	{
		bcube2 = false;

	}
  }
  if(!bcube2)
  {
    cube2RigidBody->activate(true);
    cube2RigidBody->setLinearVelocity(btVector3(10, 0, 0));
	if(cube2[3].x > -830)
	{
		bcube2 = true;
	}
  }

  if(bcube3)
  {
    cube3RigidBody->activate(true);
    cube3RigidBody->setLinearVelocity(btVector3(-10, 0, 0));
	if(cube3[3].x < 450)
	{
		bcube3 = false;

	}
  }
  if(!bcube3)
  {
    cube3RigidBody->activate(true);
    cube3RigidBody->setLinearVelocity(btVector3(10, 0, 0));
	if(cube3[3].x > 490)
	{
		bcube3 = true;
	}
  }

  if(bcube4)
  {
    cube4RigidBody->activate(true);
    cube4RigidBody->setLinearVelocity(btVector3(-10, 0, 0));
	if(cube4[3].x < 510)
	{
		bcube4 = false;

	}
  }
  if(!bcube4)
  {
    cube4RigidBody->activate(true);
    cube4RigidBody->setLinearVelocity(btVector3(10, 0, 0));
	if(cube4[3].x > 550)
	{
		bcube4 = true;
	}
  }

  if(bcube5)
  {
    cube5RigidBody->activate(true);
    cube5RigidBody->setLinearVelocity(btVector3(-10, 0, 0));
	if(cube5[3].x < 480)
	{
		bcube5 = false;

	}
  }
  if(!bcube5)
  {
    cube5RigidBody->activate(true);
    cube5RigidBody->setLinearVelocity(btVector3(10, 0, 0));
	if(cube5[3].x > 520)
	{
		bcube5 = true;
	}
  }

  if(bcube6)
  {
    cube6RigidBody->activate(true);
    cube6RigidBody->setLinearVelocity(btVector3(-10, 0, 0));
	if(cube6[3].x < 480)
	{
		bcube6 = false;

	}
  }
  if(!bcube6)
  {
    cube6RigidBody->activate(true);
    cube6RigidBody->setLinearVelocity(btVector3(10, 0, 0));
	if(cube6[3].x > 520)
	{
		bcube6 = true;
	}
  }



//LEVEL 5 MOVING METAL CUBES///////////////////////////////////////////////////////////////////////////////////
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  /*/ Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 
  glUniform1i(m_gSampler,1);*/

  glUniformMatrix4fv(m_Projection, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 
  glUniform4fv(m_LightPosition,1,glm::value_ptr(glm::vec4(10.0, 10.0, 0.0, 0.0)));
  glUniform4fv(m_AmbientProduct,1,glm::value_ptr(amb));
  glUniform4fv(m_DiffuseProduct,1,glm::value_ptr(glm::vec4(1.0, 1.0, 1.0, 1.0)));
  glUniform4fv(m_SpecularProduct,1,glm::value_ptr(glm::vec4(1.0, 1.0, 1.0, 1.0)));
  glUniform1i(m_gSampler,1);
  glUniform1f(m_Shininess,1.0);

  // Render the object
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_ball->GetModel()));
  m_ball->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_level1->GetModel()));
  m_level1->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_level2->GetModel()));
  m_level2->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_level3->GetModel()));
  m_level3->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_level4->GetModel()));
  m_level4->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_level5->GetModel()));
  m_level5->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_level6d->GetModel()));
  m_level6d->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_level6j->GetModel()));
  m_level6j->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
  m_cylinder->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder1->GetModel()));
  m_cylinder1->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder2->GetModel()));
  m_cylinder2->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder3->GetModel()));
  m_cylinder3->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder4->GetModel()));
  m_cylinder4->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder5->GetModel()));
  m_cylinder5->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder6->GetModel()));
  m_cylinder6->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder7->GetModel()));
  m_cylinder7->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder8->GetModel()));
  m_cylinder8->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder9->GetModel()));
  m_cylinder9->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder10->GetModel()));
  m_cylinder10->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder11->GetModel()));
  m_cylinder11->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder12->GetModel()));
  m_cylinder12->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder13->GetModel()));
  m_cylinder13->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder14->GetModel()));
  m_cylinder14->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder15->GetModel()));
  m_cylinder15->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder16->GetModel()));
  m_cylinder16->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder17->GetModel()));
  m_cylinder17->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder18->GetModel()));
  m_cylinder18->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder19->GetModel()));
  m_cylinder19->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_endGoal->GetModel()));
  m_endGoal->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_endGoal1->GetModel()));
  m_endGoal1->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_endGoal2->GetModel()));
  m_endGoal2->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_endGoal3->GetModel()));
  m_endGoal3->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_endGoal4->GetModel()));
  m_endGoal4->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_endGoal5->GetModel()));
  m_endGoal5->Render();

//LEVEL 5 MOVING METAL CUBES///////////////////////////////////////////////////////////////////////////////////
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
  m_cube->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube1->GetModel()));
  m_cube1->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube2->GetModel()));
  m_cube2->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube3->GetModel()));
  m_cube3->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube4->GetModel()));
  m_cube4->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube5->GetModel()));
  m_cube5->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube6->GetModel()));
  m_cube6->Render();
//LEVEL 5 MOVING METAL CUBES///////////////////////////////////////////////////////////////////////////////////
  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
  }
}

void Graphics::moveBox(int direction)
    {

	 btVector3 move = ballRigidBody->getLinearVelocity();
     switch(direction)
        {
         case 1:
            ballRigidBody->activate(true);
			move = move + btVector3(0, 0, 5);
			if(move.z() > 10)
			{
				move =btVector3(move.x(),move.y(),10);
			}
  			ballRigidBody->setLinearVelocity(move);
            break;

         case 2:
			ballRigidBody->activate(true);
			move = move - btVector3(0, 0, 5);
			if(move.z() < -10)
			{
				move =btVector3(move.x(),move.y(),-10);
			}
            ballRigidBody->setLinearVelocity(move);
            break;

         case 3:
			ballRigidBody->activate(true);
			move = move + btVector3(5, 0, 0);
			if(move.x() > 10)
			{
				move =btVector3(10,move.y(),move.z());
			}
            ballRigidBody->setLinearVelocity(move);
            break;

         case 4:
			ballRigidBody->activate(true);
			move = move - btVector3(5, 0, 0);
			if(move.x() < -10)
			{
				move =btVector3(-10,move.y(),move.z());
			}
            ballRigidBody->setLinearVelocity(move);
            break;

         case 5:
			ballRigidBody->activate(true);
			if(!canJump)
			{
				if(move.y() < 0.01 && move.y() >-(0.01) )
				{
					canJump=true;
				}

			}
			if(canJump)
			{
				move = move + btVector3(0, 6, 0);
            	ballRigidBody->setLinearVelocity(move);
 				//ballRigidBody->applyCentralForce(btVector3(0, 400, 0));
				std::cout<<move.y()<<std::endl;
				canJump=false;
			}
        }
    }

void Graphics::reset()
    {
	 std::cout<<"Game Reset"<<std::endl;
     ballRigidBody->activate(true);
     ballRigidBody->translate(btVector3(0, 0, -25)- ballRigidBody->getCenterOfMassPosition());
     score = 0;
     numBalls = 3;
     gameOver = false;
     lostBall = false;
    }

std::string Graphics::ErrorString(GLenum error)
{
  if(error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
  }

  else if(error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if(error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
  }

  else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
  }

  else if(error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
  }
  else
  {
    return "None";
  }
}
