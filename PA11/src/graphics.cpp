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
void *level6Ptr;

bool canJump;
bool jumping = false;

btRigidBody *tempBallRigidBody;

bool bumperCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2)
  {
    void *temp1Ptr = obj1->getCollisionObject()->getUserPointer();

    void *temp2Ptr = obj2->getCollisionObject()->getUserPointer();

    if(std::string(obj2->getCollisionShape()->getName()) == "STATICPLANE")
    {
     if(numBalls >= 1)
        {
         numBalls--;
         cout << "Lost a ball" << endl;
         cout << "Balls Left: " << numBalls << endl;
         lostBall = true;
        }
     else
        {
         gameOver = true;
         cout << "GAME OVER" << endl; 
         std::cout << "Final score: " << score << endl; 
         std::cout << "Press R to Play Again" << endl;
        }
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
        tempBallRigidBody->translate(btVector3(-650, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
    }

    else if(temp1Ptr == endGoal3Ptr || temp2Ptr == endGoal3Ptr)
    {
        cout << "C3" << endl;
        score ++;
        std::cout << "Score: " << score << endl;
        tempBallRigidBody->activate(true);
        tempBallRigidBody->setLinearVelocity(btVector3(0,0,0));
        tempBallRigidBody->translate(btVector3(0, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
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
        tempBallRigidBody->translate(btVector3(-450, 0, -25)- tempBallRigidBody->getCenterOfMassPosition());
    }

    if(temp1Ptr == level1Ptr || temp2Ptr == level1Ptr)
    {
        canJump = true;
    }

    else if(temp1Ptr == level2Ptr || temp2Ptr == level2Ptr)
    {
        canJump = true;
        //cout << "can jump again!" << endl;
    }

    else if(temp1Ptr == level3Ptr || temp2Ptr == level3Ptr)
    {
        canJump = true;
        //cout << "can jump again!" << endl;
    }

    else if(temp1Ptr == level4Ptr || temp2Ptr == level4Ptr)
    {
        canJump = true;
        //cout << "can jump again!" << endl;
    }

    else if(temp1Ptr == level5Ptr || temp2Ptr == level5Ptr)
    {
        canJump = true;
        //cout << "can jump again!" << endl;
    }

    else if(temp1Ptr == level6Ptr || temp2Ptr == level6Ptr)
    {
        canJump = true;
        //cout << "can jump again!" << endl;
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

/*
  btTriangleMesh *objTriMesh5 = new btTriangleMesh();
  m_level5 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/rectanglefloor.obj", true, objTriMesh5);
  level5 = new btBvhTriangleMeshShape(objTriMesh5, true);
  level5MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo level5RigidBodyCI(0, level5MotionState, level5, btVector3(0, 0, 0));
  level5RigidBody = new btRigidBody(level5RigidBodyCI);
  level5RigidBody->setUserPointer(level5RigidBody);
  level5Ptr = level5RigidBody->getUserPointer();
  cout << level5Ptr << endl;
  dynamicsWorld->addRigidBody(level5RigidBody);
  level5RigidBody->setCollisionFlags(level5RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  btTriangleMesh *objTriMesh6 = new btTriangleMesh();
  m_level6 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/rectanglefloor.obj", true, objTriMesh6);
  level6 = new btBvhTriangleMeshShape(objTriMesh6, true);
  level6MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo level6RigidBodyCI(0, level6MotionState, level6, btVector3(0, 0, 0));
  level6RigidBody = new btRigidBody(level6RigidBodyCI);
  level6RigidBody->setUserPointer(level6RigidBody);
  level6Ptr = level6RigidBody->getUserPointer();
  cout << level6Ptr << endl;
  dynamicsWorld->addRigidBody(level6RigidBody);
  level6RigidBody->setCollisionFlags(level6RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
*/

  m_ball = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/ball.obj", false, NULL);
  ball = new btSphereShape (1);
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -25)));
  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(1, ballMotionState, ball, btVector3(0, 0, 0));
  ballRigidBody = new btRigidBody(ballRigidBodyCI);
  dynamicsWorld->addRigidBody(ballRigidBody);
  ballRigidBody->setRestitution(1.0);
  ballRigidBody->setGravity(btVector3(0, -9.8, 0));
  tempBallRigidBody = ballRigidBody;

  m_endGoal = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  endGoal = new btBoxShape (btVector3(1, 1, 1));
  endGoalMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(5, 0, 5)));
  btRigidBody::btRigidBodyConstructionInfo endGoalRigidBodyCI(0, endGoalMotionState, endGoal, btVector3(0, 0, 0));
  endGoalRigidBody = new btRigidBody(endGoalRigidBodyCI);  
  endGoalRigidBody->setUserPointer(endGoalRigidBody);
  endGoalPtr = endGoalRigidBody->getUserPointer();
  cout << endGoalPtr << endl;
  dynamicsWorld->addRigidBody(endGoalRigidBody);
  endGoalRigidBody->setCollisionFlags(endGoalRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);


  m_endGoal1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  endGoal1 = new btBoxShape (btVector3(1, 1, 1));
  endGoal1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-203, 0, 65)));
  btRigidBody::btRigidBodyConstructionInfo endGoal1RigidBodyCI(0, endGoal1MotionState, endGoal1, btVector3(0, 0, 0));
  endGoal1RigidBody = new btRigidBody(endGoal1RigidBodyCI);
  endGoal1RigidBody->setUserPointer(endGoal1RigidBody);
  endGoal1Ptr = endGoal1RigidBody->getUserPointer();
  cout << endGoal1Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal1RigidBody);
  endGoal1RigidBody->setCollisionFlags(endGoal1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_endGoal2 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  endGoal2 = new btBoxShape (btVector3(1, 1, 1));
  endGoal2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-450, 0, 80)));
  btRigidBody::btRigidBodyConstructionInfo endGoal2RigidBodyCI(0, endGoal2MotionState, endGoal2, btVector3(0, 0, 0));
  endGoal2RigidBody = new btRigidBody(endGoal2RigidBodyCI);
  endGoal2RigidBody->setUserPointer(endGoal2RigidBody);
  endGoal2Ptr = endGoal2RigidBody->getUserPointer();
  cout << endGoal2Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal2RigidBody);
  endGoal2RigidBody->setCollisionFlags(endGoal2RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_endGoal3 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  endGoal3 = new btBoxShape (btVector3(1, 1, 1));
  endGoal3MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(5, 0, -5)));
  btRigidBody::btRigidBodyConstructionInfo endGoal3RigidBodyCI(0, endGoal3MotionState, endGoal3, btVector3(0, 0, 0));
  endGoal3RigidBody = new btRigidBody(endGoal3RigidBodyCI);
  endGoal3RigidBody->setUserPointer(endGoal3RigidBody);
  endGoal3Ptr = endGoal3RigidBody->getUserPointer();
  cout << endGoal3Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal3RigidBody);
  endGoal3RigidBody->setCollisionFlags(endGoal3RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_endGoal4 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  endGoal4 = new btBoxShape (btVector3(1, 1, 1));
  endGoal4MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, 0, -5)));
  btRigidBody::btRigidBodyConstructionInfo endGoal4RigidBodyCI(0, endGoal4MotionState, endGoal4, btVector3(0, 0, 0));
  endGoal4RigidBody = new btRigidBody(endGoal4RigidBodyCI);
  endGoal4RigidBody->setUserPointer(endGoal4RigidBody);
  endGoal4Ptr = endGoal4RigidBody->getUserPointer();
  cout << endGoal4Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal4RigidBody);  
  endGoal4RigidBody->setCollisionFlags(endGoal4RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_endGoal5 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  endGoal5 = new btBoxShape (btVector3(1, 1, 1));
  endGoal5MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, 0, 8)));
  btRigidBody::btRigidBodyConstructionInfo endGoal5RigidBodyCI(0, endGoal5MotionState, endGoal5, btVector3(0, 0, 0));
  endGoal5RigidBody = new btRigidBody(endGoal5RigidBodyCI);
  endGoal5RigidBody->setUserPointer(endGoal5RigidBody);
  endGoal5Ptr = endGoal5RigidBody->getUserPointer();
  cout << endGoal5Ptr << endl;
  dynamicsWorld->addRigidBody(endGoal5RigidBody);  
  endGoal5RigidBody->setCollisionFlags(endGoal5RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/cylindar.obj", false, NULL);
  cylinder = new btCylinderShape(btVector3(1, 1, 1));
  cylinderMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, 0, 0)));
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMotionState, cylinder, btVector3(0, 0, 0));
  cylinderRigidBody = new btRigidBody(cylinderRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinderRigidBody);
  cylinderRigidBody->setRestitution(1.0);
  cylinderRigidBody->setCollisionFlags(cylinderRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/cylindar.obj", false, NULL);
  cylinder1 = new btCylinderShape(btVector3(1, 1, 1));
  cylinder1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(5, 0, 0)));
  btRigidBody::btRigidBodyConstructionInfo cylinder1RigidBodyCI(0, cylinder1MotionState, cylinder1, btVector3(0, 0, 0));
  cylinder1RigidBody = new btRigidBody(cylinder1RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder1RigidBody);
  cylinder1RigidBody->setRestitution(1.0);
  cylinder1RigidBody->setCollisionFlags(cylinder1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder2 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/cylindar.obj", false, NULL);
  cylinder2 = new btCylinderShape(btVector3(1, 1, 1));
  cylinder2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -5)));
  btRigidBody::btRigidBodyConstructionInfo cylinder2RigidBodyCI(0, cylinder2MotionState, cylinder2, btVector3(0, 0, 0));
  cylinder2RigidBody = new btRigidBody(cylinder2RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder2RigidBody);
  cylinder2RigidBody->setRestitution(1.0);
  cylinder2RigidBody->setCollisionFlags(cylinder2RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  /*
  m_cube = new Object(vertexFile, fragmentFile, "../models/box.obj", false, NULL);
  cube = new btBoxShape (btVector3(1, 1, 1));
  cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-28, 0, -10)));
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(1, cubeMotionState, cube, btVector3(0, 0, 0));
  cubeRigidBody = new btRigidBody(cubeRigidBodyCI);
  dynamicsWorld->addRigidBody(cubeRigidBody);
  */

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
     ballRigidBody->translate(btVector3(0, 0, -25)- ballRigidBody->getCenterOfMassPosition());
     ballRigidBody->setLinearVelocity(btVector3(0,0,0));
     lostBall = false;
    }

  else if(gameOver == true)
    {
     gameOver = false;
     ballRigidBody->activate(true);
     ballRigidBody->translate(btVector3(0, 0, -25)- ballRigidBody->getCenterOfMassPosition());
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
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
  m_cylinder->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder1->GetModel()));
  m_cylinder1->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder2->GetModel()));
  m_cylinder2->Render();

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
			//if(!canJump)
			//{
				//if(move.y() < 1 && move.y() >-1 )
				//{
					//canJump=true;
				//}
                //else
				//{
					//std::cout<<move.y()<<"  no jump"<<std::endl;
				//}
			//}
			if(jumping == true && canJump == true)
			{
                jumping = false;
            }

            else if(jumping == false && canJump == true)
            {
                jumping = true;
                canJump=false;
				move = move + btVector3(0, 5, 0);
            	ballRigidBody->setLinearVelocity(move);
 				//ballRigidBody->applyCentralForce(btVector3(0, 400, 0));
				std::cout<<move.y()<<std::endl;
            }

            else if(jumping == true && canJump == false)
            {
                
            }
            
            else
            {
                canJump = true;
            }

			/*if(jumping == true && canJump == true)
			{
                if(canJump == true && jumping == true)
                {
                    jumping = false;
                }

                else
                {
                    jumping = true;
                    canJump=false;
				    move = move + btVector3(0, 5, 0);
            	    ballRigidBody->setLinearVelocity(move);
 				    //ballRigidBody->applyCentralForce(btVector3(0, 400, 0));
				    std::cout<<move.y()<<std::endl;
                }
            }*/

            //else
            //{
                //if(canJump == true)
                //{
                    //jumping = false;
                //}
            //}

        }
    }

void Graphics::reset()
    {
     ballRigidBody->activate(true);
     ballRigidBody->translate(btVector3(0, -1, -25)- ballRigidBody->getCenterOfMassPosition());
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
