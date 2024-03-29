
#include "engine.h"

Engine::Engine(string name, int width, int height, string vFile, string fFile, string mFile)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
  m_ROTATION_FLIP = true;
  m_TRANSLATION_FLIP = true;
  m_PAUSE = 0;

  vertexFile = vFile;
  fragmentFile = fFile;
  modelFile = mFile;
}

Engine::Engine(string name, string vFile, string fFile, string mFile)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
  m_ROTATION_FLIP = true;
  m_TRANSLATION_FLIP = true;
  m_PAUSE = 0;

  vertexFile = vFile;
  fragmentFile = fFile;
  modelFile = mFile;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics(vertexFile, fragmentFile, modelFile);
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();

      Mouse();
    }

    // Update and render the graphics
    m_graphics->Update(m_DT,m_ROTATION_FLIP,m_TRANSLATION_FLIP,m_PAUSE,m_ROTATION_FLIP_MOON,m_TRANSLATION_FLIP_MOON,m_PAUSE_MOON);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {

    // handle key down events here
    
	switch(m_event.key.keysym.sym)
	{
	  case SDLK_ESCAPE:
	    m_running = false;
	    break;

	  case SDLK_a: 
		m_TRANSLATION_FLIP = !m_TRANSLATION_FLIP; 
	    break; 
	
	  case SDLK_s: 
		m_PAUSE = 2;
	    break;

	  case SDLK_d: 
		m_PAUSE = 3;
	    break;

	  case SDLK_z: 
	    m_PAUSE = 1;
	    break;

	  case SDLK_x: 
	    m_PAUSE = 0;
	    break;

      case SDLK_LEFT: 
		m_TRANSLATION_FLIP = false; 
	    break; 

      case SDLK_RIGHT: 
		m_TRANSLATION_FLIP = true; 
	    break;

      case SDLK_g: 
		m_ROTATION_FLIP_MOON = false; 
	    break; 

      case SDLK_h: 
		m_ROTATION_FLIP_MOON = true; 
	    break;

      case SDLK_n: 
		m_TRANSLATION_FLIP_MOON = false; 
	    break; 

      case SDLK_m: 
		m_TRANSLATION_FLIP_MOON = true; 
	    break;

	  case SDLK_b: 
		m_PAUSE_MOON = 2;
	    break;

	  case SDLK_v: 
		m_PAUSE_MOON = 3;
	    break;

      case SDLK_j: 
		m_PAUSE_MOON = 4;
	    break;

	  case SDLK_k: 
		m_PAUSE_MOON = 5;
	    break;

	}
  }
}

void Engine::Mouse()
{
if (m_event.type == SDL_MOUSEBUTTONDOWN)
  {
    // handle mouse events here
    if(m_event.button.button == SDL_BUTTON_LEFT)
    {
      m_ROTATION_FLIP = !m_ROTATION_FLIP;
    }
	if(m_event.button.button == SDL_BUTTON_RIGHT)
	{
	  m_PAUSE = 4;
	}
	if(m_event.button.button == SDL_BUTTON_MIDDLE)
	{
	  m_PAUSE = 5;
	}
  }

}
unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
