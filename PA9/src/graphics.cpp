#include "graphics.h"
#include <btBulletDynamicsCommon.h>
#include <iostream>

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
  dynamicsWorld->setGravity(btVector3(0, -1, 0));

}

Graphics::~Graphics()
{
  delete broadphase;
  broadphase = NULL;

  delete collisionConfiguration;
  collisionConfiguration = NULL;

  delete dispatcher;
  dispatcher = NULL;

  delete solver;
  solver = NULL;

  delete dynamicsWorld;
  dynamicsWorld = NULL;
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

  // Create the object
  m_ball = new Object("../shaders/fragmentvl.frag", "../shaders/vertexvl.vert", "../models/ball.obj", false, NULL);
  ball = new btSphereShape (1);
  ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(1, ballMotionState, ball, btVector3(0, 0, 0));
  ballRigidBody = new btRigidBody(ballRigidBodyCI);
  dynamicsWorld->addRigidBody(ballRigidBody);

  m_cube = new Object(vertexFile, fragmentFile, "../models/box.obj", false, NULL);
  cube = new btBoxShape (btVector3(1, 1, 1));
  cubeMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(3, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo cubeRigidBodyCI(5, cubeMotionState, cube, btVector3(0, 0, 0));
  cubeRigidBody = new btRigidBody(cubeRigidBodyCI);
  dynamicsWorld->addRigidBody(cubeRigidBody);
  cubeRigidBody->setActivationState(true);
  cubeRigidBody->activate(true);

  m_cylinder = new Object(vertexFile, fragmentFile, "../models/cylindar.obj", false, NULL);
  cylinder = new btCylinderShape(btVector3(1, 1, 1));
  cylinderMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-3, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo cylinderRigidBodyCI(0, cylinderMotionState, cylinder, btVector3(0, 1, 0));
  cylinderRigidBody = new btRigidBody(cylinderRigidBodyCI);
  dynamicsWorld->addRigidBody(cylinderRigidBody);

  btTriangleMesh *objTriMesh1 = new btTriangleMesh();
  m_walls = new Object(vertexFile, fragmentFile, "../models/board2.obj", true, objTriMesh1);
  walls = new btBvhTriangleMeshShape(objTriMesh1, true);
  wallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(1, -1, 0)));
  btRigidBody::btRigidBodyConstructionInfo wallRigidBodyCI(0, wallMotionState, walls, btVector3(0, 0, 0));
  wallRigidBody = new btRigidBody(wallRigidBodyCI);
  dynamicsWorld->addRigidBody(wallRigidBody);
  
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
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_gSampler not found\n");
    return false;
  } 

  // Locate the ModelView
  m_ModelView = m_shader->GetUniformLocation("ModelView");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_ModelView not found\n");
    return false;
  } 
  // Locate the LightPosition
  m_LightPosition = m_shader->GetUniformLocation("LightPosition");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_LightPosition not found\n");
    return false;
  } 
  // Locate the Projection
  m_Projection = m_shader->GetUniformLocation("Projection");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_Projection not found\n");
    return false;
  } 

  // Locate the Shininess
  m_Shininess = m_shader->GetUniformLocation("Shininess");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_Shininess not found\n");
    return false;
  } 

  // Locate the AmbientProduct
  m_AmbientProduct = m_shader->GetUniformLocation("AmbientProduct");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_AmbientProduct not found\n");
    return false;
  } 

  // Locate the DiffuseProduct
  m_DiffuseProduct = m_shader->GetUniformLocation("DiffuseProduct");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_DiffuseProduct not found\n");
    return false;
  } 

  // Locate the SpecularProduct
  m_SpecularProduct = m_shader->GetUniformLocation("SpecularProduct");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION) 
  {
    printf("m_SpecularProduct not found\n");
    return false;
  } /*
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
 

   GLfloat mat_s[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_sh[] = { 50.0 };
   GLfloat mat_a[] = {0,0,0,1};
   GLfloat mat_d[] = {1,1,1,1};
   GLfloat light_p[] = { 100.0, 100.0, 0.0, 0.0 };

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_a);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_sh);
*/

  //enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(unsigned int dt)
{
  btTransform trans;
  btScalar m[16];
  dynamicsWorld->stepSimulation(1/60.f, 10);

  ballRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  //std::cout << "ball height: " << trans.getOrigin().getY() << std::endl;
  m_ball->Update(dt, glm::make_mat4(m));

  //cubeRigidBody->applyCentralImpulse(btVector3(0, 0.1, 0));
  cubeRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  //std::cout << "cube height: " << trans.getOrigin().getY() << std::endl;
  m_cube->Update(dt, glm::make_mat4(m));

  cylinderRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  //std::cout << "cylinder height: " << trans.getOrigin().getY() << std::endl;
  m_cylinder->Update(dt, glm::make_mat4(m));

  wallRigidBody->getMotionState()->getWorldTransform(trans);
  trans.getOpenGLMatrix(m);
  //std::cout << "wall height: " << trans.getOrigin().getY() << std::endl;
  m_walls->Update(dt, glm::make_mat4(m));
}

void Graphics::Render()
{
  //clear the screen
  glClearColor(0.0, 0.0, 0.2, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();





  // Send in the projection and view to the shader
  //glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection())); 
  //glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 

  glUniformMatrix4fv(m_Projection, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_ModelView, 1, GL_FALSE, glm::value_ptr(m_camera->GetView())); 
  glUniform4fv(m_LightPosition,1,glm::value_ptr(glm::vec4(100.0, 100.0, 0.0, 0.0)));
  glUniform4fv(m_AmbientProduct,1,glm::value_ptr(glm::vec4(0.2, 0.2, 0.2, 1.0)));
  glUniform4fv(m_DiffuseProduct,1,glm::value_ptr(glm::vec4(1.0, 1.0, 1.0, 1.0)));
  glUniform4fv(m_SpecularProduct,1,glm::value_ptr(glm::vec4(1.0, 1.0, 1.0, 1.0)));
  glUniform1i(m_gSampler,1);
  glUniform1f(m_Shininess,1.0);

  // Render the object

  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_ball->GetModel()));
  m_ball->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cube->GetModel()));
  m_cube->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_cylinder->GetModel()));
  m_cylinder->Render();
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_walls->GetModel()));
  m_walls->Render();

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
            cubeRigidBody->activate(true);
            cubeRigidBody->applyCentralForce(btVector3(0, 0, 300));   
            break;

         case 2:
			cubeRigidBody->activate(true);
            cubeRigidBody->applyCentralForce(btVector3(0, 0, -300));
            break;

         case 3:
			cubeRigidBody->activate(true);	
            cubeRigidBody->applyCentralForce(btVector3(300, 0, 0));
            break;

         case 4:
			cubeRigidBody->activate(true);
            cubeRigidBody->applyCentralForce(btVector3(-300, 0, 0));
            break;   
        }
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
