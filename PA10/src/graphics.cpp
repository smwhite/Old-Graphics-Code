#include "graphics.h"
#include <btBulletDynamicsCommon.h>
#include <iostream>

int score = 0;

bool bumperCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* obj1, int id1, int index1, const btCollisionObjectWrapper* obj2, int id2, int index2)
  {
    score ++;
    std::cout << "Score: " << score << endl; 
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
  dynamicsWorld->setGravity(btVector3(0, -2.8, -2.8));
  gContactAddedCallback=bumperCallback;
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
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-28, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(1, ballMotionState, ball, btVector3(0, 0, 0));
  ballRigidBody = new btRigidBody(ballRigidBodyCI);
  dynamicsWorld->addRigidBody(ballRigidBody);
ballRigidBody->setRestitution(1.0);

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

/*
  btTriangleMesh *objTriMesh1 = new btTriangleMesh();
  m_walls = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/boardfinal.obj", true, objTriMesh1);
  walls = new btBvhTriangleMeshShape(objTriMesh1, true);
  wallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI(0, wallMotionState, walls, btVector3(0, 0, 0));
  wallRigidBody = new btRigidBody(wallRigidBodyCI);
  dynamicsWorld->addRigidBody(wallRigidBody);
*/

  btTriangleMesh *objTriMesh3 = new btTriangleMesh();
  m_lPaddle1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/paddle.obj", true, objTriMesh3);
  lPaddle1 = new btBvhTriangleMeshShape(objTriMesh3, true);
  lPaddle1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -0, 0)));
  btRigidBody::btRigidBodyConstructionInfo lPaddle1RigidBodyCI(1, lPaddle1MotionState, lPaddle1, btVector3(0, 0, 0));
  lPaddle1RigidBody = new btRigidBody(lPaddle1RigidBodyCI);
  dynamicsWorld->addRigidBody(lPaddle1RigidBody);
  lPaddle1RigidBody->setRestitution(1.0);
  //btTriangleMesh *objTriMesh3 = new btTriangleMesh();
  //m_lPaddle1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/paddle.obj", true, objTriMesh3);
  //lPaddle1 = new btBvhTriangleMeshShape(objTriMesh3, true);
  //btVector3(19, -1, -17)
  //lPaddle1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
  //btRigidBody::btRigidBodyConstructionInfo lPaddle1RigidBodyCI(1, lPaddle1MotionState, lPaddle1, btVector3(0, 0, 0));
  //lPaddle1RigidBody = new btRigidBody(lPaddle1RigidBodyCI);
  //dynamicsWorld->addRigidBody(lPaddle1RigidBody);

  //lPaddle1RigidBody->setActivationState(true);
  //lPaddle1RigidBody->setCollisionFlags(lPaddle1RigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
  //lPaddle1RigidBody->setActivationState(DISABLE_DEACTIVATION);
  //lPaddle1RigidBody->activate(true);
  

  //btTriangleMesh *objTriMesh4 = new btTriangleMesh();
  //m_rPaddle1 = new Object("../shaders/fragmentfl.frag", "../shaders/vertexfl.vert", "../models/paddle.obj", true, objTriMesh4);
  //rPaddle1 = new btBvhTriangleMeshShape(objTriMesh4, true);
  //rPaddle1MotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 2, -5)));
  //btRigidBody::btRigidBodyConstructionInfo rPaddle1RigidBodyCI(1, rPaddle1MotionState, rPaddle1, btVector3(0, 0, 0));
  //rPaddle1RigidBody = new btRigidBody(rPaddle1RigidBodyCI);
  //dynamicsWorld->addRigidBody(rPaddle1RigidBody);
  //rPaddle1RigidBody->setActivationState(true);
  //rPaddle1RigidBody->setCollisionFlags(rPaddle1RigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
  //rPaddle1RigidBody->setActivationState(DISABLE_DEACTIVATION);
  //rPaddle1RigidBody->activate(true);

  cover = new btStaticPlaneShape (btVector3(0, -1, 0), 1);
  coverMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
  btRigidBody::btRigidBodyConstructionInfo coverRigidBodyCI(0, coverMotionState, cover, btVector3(0, 0, 0));
  coverRigidBody = new btRigidBody(coverRigidBodyCI);
  dynamicsWorld->addRigidBody(coverRigidBody);
  
  // Set up the shaders
  m_shader = new Shader(vertexFile, fragmentFile);
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
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_gSampler not found\n");
    return false;
  } 

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt,float LR,float UD)
{
  // Update the object
  btTransform trans;
  btScalar m[16];
  dynamicsWorld->stepSimulation(1/60.f, 10);

  m_camera->Update(LR,UD,0.0,0.0,0.0);

  ballRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_ball->Update(dt, glm::make_mat4(m));

  wallRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  m_walls->Update(dt, glm::make_mat4(m));

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

  //rPaddle1RigidBody->getMotionState()->getWorldTransform(trans);
  //trans.getOpenGLMatrix(m);
  //m_rPaddle1->Update(dt, glm::make_mat4(m));
  


	//m_camera->Update(LR,UD,ELR,EUD,ZOOM);





}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 
  glUniform1i(m_gSampler,1);

  // Render the object
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_ball->GetModel()));
  m_ball->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_walls->GetModel()));
  m_walls->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
  m_cylinder->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder1->GetModel()));
  m_cylinder1->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder2->GetModel()));
  m_cylinder2->Render();
 
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_lPaddle1->GetModel()));
  m_lPaddle1->Render();
  //glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_rPaddle1->GetModel()));
  //m_rPaddle1->Render();

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
     switch(direction)
        {
         case 1:
            ballRigidBody->activate(true);
            ballRigidBody->applyCentralForce(btVector3(0, 0, 300));   
            break;

         case 2:
			ballRigidBody->activate(true);
            ballRigidBody->applyCentralForce(btVector3(0, 0, -300));
            break;

         case 3:
			ballRigidBody->activate(true);	
            ballRigidBody->applyCentralForce(btVector3(300, 0, 0));
            break;

         case 4:
			ballRigidBody->activate(true);
            ballRigidBody->applyCentralForce(btVector3(-300, 0, 0));
            break;   
        }
    }

void Graphics::leftPaddle()
    {
     std::cout << "bruh left" << endl;
     lPaddle1RigidBody->activate(true);
     //lPaddle1RigidBody->applyCentralForce(btVector3(-300, 0, 0));
     lPaddle1RigidBody->applyTorque(btVector3(0, 300, 0)); 
    }

void Graphics::rightPaddle()
    {
     std::cout << "bruh right" << endl;
     //btTransform newTrans;
     //rPaddle1RigidBody->getMotionState()->getWorldTransform(newTrans);
     //newTrans.getOrigin() += (btVector3(0, 0.1f, 0));
     //rPaddle1RigidBody->getMotionState()->setWorldTransform(newTrans);
     //rPaddle1RigidBody->activate(true);
     //rPaddle1RigidBody->applyCentralForce(btVector3(-300, 0, 0));
     //rPaddle1RigidBody->applyTorque(btVector3(0, 300, 0));
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

