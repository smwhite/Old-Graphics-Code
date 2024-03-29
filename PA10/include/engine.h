#ifndef ENGINE_H
#define ENGINE_H

#include <sys/time.h>
#include <assert.h>

#include "window.h"
#include "graphics.h"

class Engine
{
  public:
    Engine(string name, int width, int height, string vFile, string fFile, string mFile);
    Engine(string name, string vFile, string fFile, string mFile);
    ~Engine();
    bool Initialize();
    void Run();
    void Keyboard();
    void Mouse();
    unsigned int getDT();
    long long GetCurrentTimeMillis();
  
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
    
    string vertexFile;
    string fragmentFile;
    string modelFile;

	float LR = 0;
	float UD = -30;
	float ELR = 0;
	float EUD = 20;
	float ZOOM = -100.0;
    float multiplier = 1;
	int cameraPosition =0;
};

#endif // ENGINE_H
