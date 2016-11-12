#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  //cout << argv[1] << endl;

  // These variables were created to store and pass the 3 command line arguments for the file paths
  std::string vertFile;
  std::string fragFile;
  std::string modelFile;

  // These statements were added to see if the user gave any command line arguments. 
  // If argc is 2 then that means the user gave at least 1 file name and the program will assume it is the model file and use the default vertex and fragment shaders
  if( argc == 2)
    {
     modelFile = argv[1];
     fragFile = "../shaders/fragmentfl.frag";
     vertFile = "../shaders/vertexfl.vert";
    }

  // If argc is 3, the program will assume that the first one is the model file, and the second one is the vertex shader
  else if( argc == 3)
    {
     modelFile = argv[1];
     vertFile = argv[2];
     fragFile = "../shaders/fragmentfl.frag";
    }

  // If argc is 4 or greater, the program will assume that the first one is the model file, the second one is the vertex shader, and the third one is the fragment shader.
  else if( argc >= 4)
    {
     modelFile = argv[1];
     vertFile = argv[2];
     fragFile = argv[3];
    }

  // If Argc is 1 then that means there were no arguments given by the user and the program will default to the provided shaders and model
  else
    {
     vertFile = "../shaders/vertexfl.vert";
     fragFile = "../shaders/fragmentfl.frag";
	 modelFile = "../models/ball.obj";
    }

  //cout << vertFile << endl;
  //cout << fragFile << endl;
  //cout << modelFile << endl;

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial", 800, 600, vertFile, fragFile, modelFile);
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
