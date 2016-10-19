#include "graphics.h"

Graphics::Graphics(string vFile, string fFile, string mFile)
{
  vertexFile = vFile;
  fragmentFile = fFile;
  modelFile = mFile;
}

Graphics::~Graphics()
{

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
  m_sun = new Object(glm::mat4(1.0f),0.0f, 4000, 2500, vertexFile, fragmentFile, modelFile);
  m_mercury = new Object(glm::mat4(1.0f),3.0f, 2000, 5000, vertexFile, fragmentFile, modelFile);
  m_venus = new Object(glm::mat4(1.0f),5.0f, 1000, 1500, vertexFile, fragmentFile, modelFile);
  m_earth = new Object(glm::mat4(1.0f),7.0f, 5000, 6000, vertexFile, fragmentFile, modelFile);
  m_mars = new Object(glm::mat4(1.0f),9.0f, 1600, 2000, vertexFile, fragmentFile, modelFile);
  m_jupiter = new Object(glm::mat4(1.0f),11.0f, 3200, 5000, vertexFile, fragmentFile, modelFile);
  m_saturn = new Object(glm::mat4(1.0f),13.0f, 5500, 2000, vertexFile, fragmentFile, modelFile);
  m_neptune = new Object(glm::mat4(1.0f),15.0f, 3000, 2500, vertexFile, fragmentFile, modelFile);
  m_uranus = new Object(glm::mat4(1.0f),17.0f, 1000, 5000, vertexFile, fragmentFile, modelFile);
  m_pluto = new Object(glm::mat4(1.0f),19.0f, 1500, 1000, vertexFile, fragmentFile, modelFile);
  
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

void Graphics::Update(unsigned int dt,bool rotation,bool translation, int pause,bool moonR,bool moonT, int moonP, float LR, float UD,float ELR, float EUD, float ZOOM)
{
  // Update the object


  m_sun->Update(dt,rotation,translation,pause,glm::mat4(1.0f),1.0f);
  m_mercury->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  m_venus->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  m_earth->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  m_mars->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  m_jupiter->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  m_saturn->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  m_neptune->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  m_uranus->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  m_pluto->Update(dt,rotation,translation,pause,glm::mat4(1.0f),0.5f);
  
  m_camera->Update(LR,UD,ELR,EUD,ZOOM);
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

  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mercury->GetModel()));
  m_mercury->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_venus->GetModel()));
  m_venus->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_earth->GetModel()));
  m_earth->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_mars->GetModel()));
  m_mars->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_jupiter->GetModel()));
  m_jupiter->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_saturn->GetModel()));
  m_saturn->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_neptune->GetModel()));
  m_neptune->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_uranus->GetModel()));
  m_uranus->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_pluto->GetModel()));
  m_pluto->Render();
  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(m_sun->GetModel()));
  m_sun->Render();

  // Get any errors from OpenGL
  auto error = glGetError();
  if ( error != GL_NO_ERROR )
  {
    string val = ErrorString( error );
    std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
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

