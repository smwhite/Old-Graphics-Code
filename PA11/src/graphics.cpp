#include "graphics.h"
#include <btBulletDynamicsCommon.h>
#include <iostream>

int score = 0;
int numBalls = 3;
bool gameOver = false;
bool lostBall = false;
void *collectiblePtr;
void *collectible1Ptr;
void *collectible2Ptr;
void *collectible3Ptr;
void *collectible4Ptr;

bool bumperCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2)
  {
    void *temp1Ptr = obj1->getCollisionObject()->getUserPointer();
    cout << temp1Ptr << endl;
    void *temp2Ptr = obj2->getCollisionObject()->getUserPointer();
    cout << temp2Ptr << endl;
    /*
    if(int(obj1->getCollisionShape()->getUserIndex()) == 2 || int(obj2->getCollisionShape()->getUserIndex()) == 2)
    {
        cout << ":D1" << endl;
    }

    if(int(obj1->getCollisionShape()->getUserIndex()) == 3 || int(obj2->getCollisionShape()->getUserIndex()) == 3)
    {
        cout << ":D2" << endl;
    }

    if(int(obj1->getCollisionShape()->getUserIndex()) == 4 || int(obj2->getCollisionShape()->getUserIndex()) == 4)
    {
        cout << ":D3" << endl;
    }
    
    if(int(obj1->getCollisionShape()->getUserIndex()) == 5 || int(obj2->getCollisionShape()->getUserIndex()) == 5)
    {
        cout << ":D4" << endl;
    }
    */

    if(std::string(obj1->getCollisionShape()->getName()) == "CylinderY")
    {
     score ++;
     std::cout << "Score: " << score << endl; 
     //btCollisionObject* temp = obj1->getCollisionShape();
     //Graphics::deleteObj(temp);
    }
    else if(std::string(obj2->getCollisionShape()->getName()) == "CylinderY")
    {
     score ++;
     std::cout << "Score: " << score << endl; 
     //btCollisionObject* temp = obj2->getCollisionShape();
     //Graphics::deleteObj(temp);
    }
    else if(std::string(obj2->getCollisionShape()->getName()) == "STATICPLANE")
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

    else if(temp1Ptr == collectiblePtr || temp2Ptr == collectiblePtr)
    {
        cout << "C0" << endl;
    }

    else if(temp1Ptr == collectible1Ptr || temp2Ptr == collectible1Ptr)
    {
        cout << "C1" << endl;
    }

    else if(temp1Ptr == collectible2Ptr || temp2Ptr == collectible2Ptr)
    {
        cout << "C2" << endl;
    }

    else if(temp1Ptr == collectible3Ptr || temp2Ptr == collectible3Ptr)
    {
        cout << "C3" << endl;
    }

    else if(temp1Ptr == collectible4Ptr || temp2Ptr == collectible4Ptr)
    {
        cout << "C4" << endl;
    }

    return false;
  }

//bool lossCallback(btManifoldPoint& cp, const btCollisionObject* obj1, int id1, int index1, const btCollisionObject* obj2, int id2, int index2)
  //{
    //std::cout << "Collided with Loss Box" << endl;
    //return false;
  //}

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
  m_walls = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/boardfinal.obj", true, objTriMesh1);
  walls = new btBvhTriangleMeshShape(objTriMesh1, true);
  wallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI(0, wallMotionState, walls, btVector3(0, 0, 0));
  wallRigidBody = new btRigidBody(wallRigidBodyCI);
  dynamicsWorld->addRigidBody(wallRigidBody);

  m_ball = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/ball.obj", false, NULL);
  ball = new btSphereShape (1);
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-28, -1, -8)));
  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(1, ballMotionState, ball, btVector3(0, 0, 0));
  ballRigidBody = new btRigidBody(ballRigidBodyCI);
  dynamicsWorld->addRigidBody(ballRigidBody);
  ballRigidBody->setRestitution(1.0);
  ballRigidBody->setGravity(btVector3(0, 1, 0));

  m_collectible = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  collectible = new btBoxShape (btVector3(1, 1, 1));
  collectibleMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(5, -1, 5)));
  btRigidBody::btRigidBodyConstructionInfo collectibleRigidBodyCI(0, collectibleMotionState, collectible, btVector3(0, 0, 0));
  collectibleRigidBody = new btRigidBody(collectibleRigidBodyCI);  
  collectibleRigidBody->setUserPointer(collectibleRigidBody);
  collectiblePtr = collectibleRigidBody->getUserPointer();
  cout << collectiblePtr << endl;
  dynamicsWorld->addRigidBody(collectibleRigidBody);
  collectibleRigidBody->setCollisionFlags(collectibleRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);


  m_collectible1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  collectible1 = new btBoxShape (btVector3(1, 1, 1));
  collectible1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, -1, 5)));
  btRigidBody::btRigidBodyConstructionInfo collectible1RigidBodyCI(0, collectible1MotionState, collectible1, btVector3(0, 0, 0));
  collectible1RigidBody = new btRigidBody(collectible1RigidBodyCI);
  collectible1RigidBody->setUserPointer(collectible1RigidBody);
  collectible1Ptr = collectible1RigidBody->getUserPointer();
  cout << collectible1Ptr << endl;
  dynamicsWorld->addRigidBody(collectible1RigidBody);
  collectible1RigidBody->setCollisionFlags(collectible1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_collectible2 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  collectible2 = new btBoxShape (btVector3(1, 1, 1));
  collectible2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 5)));
  btRigidBody::btRigidBodyConstructionInfo collectible2RigidBodyCI(0, collectible2MotionState, collectible2, btVector3(0, 0, 0));
  collectible2RigidBody = new btRigidBody(collectible2RigidBodyCI);
  collectible2RigidBody->setUserPointer(collectible2RigidBody);
  collectible2Ptr = collectible2RigidBody->getUserPointer();
  cout << collectible2Ptr << endl;
  dynamicsWorld->addRigidBody(collectible2RigidBody);
  collectible2RigidBody->setCollisionFlags(collectible2RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_collectible3 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  collectible3 = new btBoxShape (btVector3(1, 1, 1));
  collectible3MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(5, -1, -5)));
  btRigidBody::btRigidBodyConstructionInfo collectible3RigidBodyCI(0, collectible3MotionState, collectible3, btVector3(0, 0, 0));
  collectible3RigidBody = new btRigidBody(collectible3RigidBodyCI);
  collectible3RigidBody->setUserPointer(collectible3RigidBody);
  collectible3Ptr = collectible3RigidBody->getUserPointer();
  cout << collectible3Ptr << endl;
  dynamicsWorld->addRigidBody(collectible3RigidBody);
  collectible3RigidBody->setCollisionFlags(collectible3RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_collectible4 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/box.obj", false, NULL);
  collectible4 = new btBoxShape (btVector3(1, 1, 1));
  collectible4MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, -1, -5)));
  btRigidBody::btRigidBodyConstructionInfo collectible4RigidBodyCI(0, collectible4MotionState, collectible4, btVector3(0, 0, 0));
  collectible4RigidBody = new btRigidBody(collectible4RigidBodyCI);
  collectible4RigidBody->setUserPointer(collectible4RigidBody);
  collectible4Ptr = collectible4RigidBody->getUserPointer();
  cout << collectible4Ptr << endl;
  dynamicsWorld->addRigidBody(collectible4RigidBody);  
  collectible4RigidBody->setCollisionFlags(collectible4RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/cylindar.obj", false, NULL);
  cylinder = new btCylinderShape(btVector3(1, 1, 1));
  cylinderMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-5, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMotionState, cylinder, btVector3(0, 0, 0));
  cylinderRigidBody = new btRigidBody(cylinderRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinderRigidBody);
  cylinderRigidBody->setRestitution(1.0);
  cylinderRigidBody->setCollisionFlags(cylinderRigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/cylindar.obj", false, NULL);
  cylinder1 = new btCylinderShape(btVector3(1, 1, 1));
  cylinder1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(5, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo cylinder1RigidBodyCI(0, cylinder1MotionState, cylinder1, btVector3(0, 0, 0));
  cylinder1RigidBody = new btRigidBody(cylinder1RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder1RigidBody);
  cylinder1RigidBody->setRestitution(1.0);
  cylinder1RigidBody->setCollisionFlags(cylinder1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);

  m_cylinder2 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/cylindar.obj", false, NULL);
  cylinder2 = new btCylinderShape(btVector3(1, 1, 1));
  cylinder2MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, -5)));
  btRigidBody::btRigidBodyConstructionInfo cylinder2RigidBodyCI(0, cylinder2MotionState, cylinder2, btVector3(0, 0, 0));
  cylinder2RigidBody = new btRigidBody(cylinder2RigidBodyCI);
  dynamicsWorld->addRigidBody(cylinder2RigidBody);
  cylinder2RigidBody->setRestitution(1.0);
  cylinder2RigidBody->setCollisionFlags(cylinder2RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);


  m_cube = new Object(vertexFile, fragmentFile, "../models/box.obj", false, NULL);
  cube = new btBoxShape (btVector3(1, 1, 1));
  cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-28, 0, -10)));
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(1, cubeMotionState, cube, btVector3(0, 0, 0));
  cubeRigidBody = new btRigidBody(cubeRigidBodyCI);
  dynamicsWorld->addRigidBody(cubeRigidBody);
  //cubeRigidBody->setGravity(btVector3(0, -6.8, -6.8));

  m_backboard = new Object(vertexFile, fragmentFile, "../models/backboard.obj", false, NULL);

  m_lPaddle1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/left.obj",false, NULL);
  lPaddle1 = new btBoxShape (btVector3(1, 1, 1));
  lPaddle1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(19, 1, -21)));
  btRigidBody::btRigidBodyConstructionInfo lPaddle1RigidBodyCI(0, lPaddle1MotionState, lPaddle1, btVector3(0, 1, 0));
  lPaddle1RigidBody = new btRigidBody(lPaddle1RigidBodyCI);
  dynamicsWorld->addRigidBody(lPaddle1RigidBody);
  lPaddle1RigidBody->setRestitution(1.0);
  lPaddle1RigidBody-> setLinearVelocity(btVector3(0,0,0));
  btTransform newTrans;
  btQuaternion rot;
  rot.setEuler(-10, 0, 0);
  lPaddle1RigidBody->getMotionState()->getWorldTransform(newTrans);
  newTrans.setRotation(rot);
  lPaddle1RigidBody->getMotionState()->setWorldTransform(newTrans);
  lPaddle1RigidBody->setActivationState(true);

  m_rPaddle1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/right.obj",false, NULL);
  rPaddle1 = new btBoxShape (btVector3(1, 1, 1));
  rPaddle1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-10, 1, -21)));
  btRigidBody::btRigidBodyConstructionInfo rPaddle1RigidBodyCI(0, rPaddle1MotionState, rPaddle1, btVector3(0, 1, 0));
  rPaddle1RigidBody = new btRigidBody(rPaddle1RigidBodyCI);
  dynamicsWorld->addRigidBody(rPaddle1RigidBody);
  rPaddle1RigidBody->setRestitution(1.0);
  rPaddle1RigidBody-> setLinearVelocity(btVector3(0,0,0));
  rot.setEuler(10, 0, 0);
  rPaddle1RigidBody->getMotionState()->getWorldTransform(newTrans);
  newTrans.setRotation(rot);
  rPaddle1RigidBody->getMotionState()->setWorldTransform(newTrans);
  rPaddle1RigidBody->setActivationState(true);


  //cover = new btStaticPlaneShape (btVector3(0, -1, 0), 1);
  //coverMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
  //btRigidBody::btRigidBodyConstructionInfo coverRigidBodyCI(0, coverMotionState, cover, btVector3(0, 0, 0));
  //coverRigidBody = new btRigidBody(coverRigidBodyCI);
  //dynamicsWorld->addRigidBody(coverRigidBody);

  loss = new btStaticPlaneShape (btVector3(0, 0, 1), 1);
  lossMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, -30)));
  btRigidBody::btRigidBodyConstructionInfo lossRigidBodyCI(0, lossMotionState, loss, btVector3(0, 0, 0));
  lossRigidBody = new btRigidBody(lossRigidBodyCI);
  dynamicsWorld->addRigidBody(lossRigidBody);
  lossRigidBody->setCollisionFlags(cylinder1RigidBody->getCollisionFlags() | btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK);
  //lossRigidBody->setUserIndex(2);
  
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
     ballRigidBody->translate(btVector3(-28, -1, -8)- ballRigidBody->getCenterOfMassPosition());
     //btTransform newTrans;
     //ballRigidBody->getMotionState()->getWorldTransform(newTrans);
     //newTrans.getOrigin() = (btVector3(-28, -1, -8));
     //ballRigidBody->getMotionState()->setWorldTransform(newTrans);
     lostBall = false;
    }

  else if(gameOver == true)
    {
     gameOver = false;
     ballRigidBody->activate(true);
     ballRigidBody->translate(btVector3(-28, -1, -8)- ballRigidBody->getCenterOfMassPosition());
     //btTransform newTrans;
     //ballRigidBody->getMotionState()->getWorldTransform(newTrans);
     //newTrans.getOrigin() = (btVector3(-28, -1, -8));
     //ballRigidBody->getMotionState()->setWorldTransform(newTrans);
    }
  // Update the object
  btTransform trans;
  btScalar m[16];
  dynamicsWorld->stepSimulation(1/60.f, 10);


  //btTransform newTrans;
  //lPaddle1RigidBody->getMotionState()->getWorldTransform(newTrans);
  //lPaddle1RigidBody->getMotionState()->setWorldTransform(newTrans);


  ballRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_ball->Update(dt, glm::make_mat4(m));

  glm::mat4 test = glm::make_mat4(m);
  m_camera->Update(test[3].x,test[3].z,0.0,0.0,0.0);

  wallRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_walls->Update(dt, glm::make_mat4(m));

  collectibleRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_collectible->Update(dt, glm::make_mat4(m));
  collectible1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_collectible1->Update(dt, glm::make_mat4(m));
  collectible2RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_collectible2->Update(dt, glm::make_mat4(m));
  collectible3RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_collectible3->Update(dt, glm::make_mat4(m));
  collectible4RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_collectible4->Update(dt, glm::make_mat4(m));

  cylinderRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder->Update(dt, glm::make_mat4(m));

  cylinder1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder1->Update(dt, glm::make_mat4(m));

  cylinder2RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cylinder2->Update(dt, glm::make_mat4(m));

  lPaddle1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_lPaddle1->Update(dt, glm::make_mat4(m));

  cubeRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_cube->Update(dt, glm::make_mat4(m));

  rPaddle1RigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_rPaddle1->Update(dt, glm::make_mat4(m));
  


	//m_camera->Update(LR,UD,ELR,EUD,ZOOM);





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
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_walls->GetModel()));
  m_walls->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
  m_cylinder->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder1->GetModel()));
  m_cylinder1->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder2->GetModel()));
  m_cylinder2->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_collectible->GetModel()));
  m_collectible->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_collectible1->GetModel()));
  m_collectible1->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_collectible2->GetModel()));
  m_collectible2->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_collectible3->GetModel()));
  m_collectible3->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_collectible4->GetModel()));
  m_collectible4->Render();
 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_lPaddle1->GetModel()));
  m_lPaddle1->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_rPaddle1->GetModel()));
  m_rPaddle1->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
  m_cube->Render();

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_backboard->GetModel()));
  m_backboard->Render();

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
            //ballRigidBody->applyCentralForce(btVector3(0, 0, 300));
			move = move + btVector3(0, 0, 5);
			if(move.z() > 15)
			{
				move =btVector3(move.x(),move.y(),15);
			}
  			ballRigidBody->setLinearVelocity(move);
            break;

         case 2:
			ballRigidBody->activate(true);
			move = move - btVector3(0, 0, 5);
			if(move.z() < -15)
			{
				move =btVector3(move.x(),move.y(),-15);
			}
            ballRigidBody->setLinearVelocity(move);
            break;

         case 3:
			ballRigidBody->activate(true);
			move = move + btVector3(5, 0, 0);
			if(move.x() > 15)
			{
				move =btVector3(15,move.y(),move.z());
			}
            ballRigidBody->setLinearVelocity(move);
            break;

         case 4:
			ballRigidBody->activate(true);
			move = move - btVector3(5, 0, 0);
			if(move.x() < -15)
			{
				move =btVector3(-15,move.y(),move.z());
			}
            ballRigidBody->setLinearVelocity(move);
            break;

         case 5:
			ballRigidBody->activate(true);
			if(!canJump)
			{
				if(move.y() == 0)
				{
					canJump=true;
				}
			}
			if(canJump)
			{
				move = move + btVector3(0, 10, 0);
            	ballRigidBody->setLinearVelocity(move);
			}
            break;

        }
    }

void Graphics::leftPaddle()
    {
     btTransform newTr;
     btQuaternion rot;
     rot.setEuler(10, 0, 0);
     lPaddle1RigidBody->getMotionState()->getWorldTransform(newTr);
     newTr.setRotation(rot);
     lPaddle1RigidBody->getMotionState()->setWorldTransform(newTr);

     for(int i  = 0; i < 1000; i++)
        {

        }

     rot.setEuler(-10, 0, 0);
     lPaddle1RigidBody->getMotionState()->getWorldTransform(newTr);
     newTr.setRotation(rot);
     lPaddle1RigidBody->getMotionState()->setWorldTransform(newTr);

    }

void Graphics::rightPaddle()
    {
     btTransform newTr;
     btQuaternion rot;
     rot.setEuler(-10, 0, 0);
     rPaddle1RigidBody->getMotionState()->getWorldTransform(newTr);
     newTr.setRotation(rot);
     rPaddle1RigidBody->getMotionState()->setWorldTransform(newTr);
     
     for(int i  = 0; i < 1000; i++)
        {
           
        }

     rot.setEuler(10, 0, 0);
     rPaddle1RigidBody->getMotionState()->getWorldTransform(newTr);
     newTr.setRotation(rot);
     rPaddle1RigidBody->getMotionState()->setWorldTransform(newTr);
    }

void Graphics::reset()
    {
     ballRigidBody->activate(true);
     ballRigidBody->translate(btVector3(-28, -1, -8)- ballRigidBody->getCenterOfMassPosition());
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

void Graphics::deleteObj(btCollisionObject* obj)
{
    cout << "Blah" << endl;
}
