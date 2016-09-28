#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "window.h"
#include "graphics.h"

class Engine
{
  public:
    Engine(string name, int width, int height, std::string File);
    Engine(string name);
    ~Engine();
    bool Initialize();
    void Run();
    void Keyboard();
    void Mouse();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
    string ModelFile;
  
  private:
    // Window related variables
    Window *m_window;    
    string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;
	
	// Variables for changing object movement
    bool m_ROTATION_FLIP;
    bool m_TRANSLATION_FLIP;
    int m_PAUSE;
    bool m_ROTATION_FLIP_MOON;
    bool m_TRANSLATION_FLIP_MOON;
    int m_PAUSE_MOON;

    Graphics *m_graphics;
    unsigned int m_DT;
    long long m_currentTimeMillis;
    bool m_running;
};

#endif // ENGINE_H
