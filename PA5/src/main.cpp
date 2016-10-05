#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  // These variables were created to store and pass the 3 command line arguments for the file paths
  char* vertFile;
  char* fragFile;
  char* modelFile;

  // These statements were added to see if the user gave any command line arguments. 
  // If argc is 2 then that means the user gave at least 1 file name and the program will assume it is the vertex file and use the fragment shader that is located in shaders
  if( argc == 2)
    {
     vertFile = argv[1];
     fragFile = "fragment.frag";
     modelFile = "test.obj";
    }

  if( argc == 3)
    {
     vertFile = argv[1];
     fragFile = argv[2];
     modelFile = "test.obj";
    }

  // If argc is 3 or greater, the program will assume that the first one is the vertex shader and the second one is the fragment shader.
  else if( argc >= 4)
    {
     vertFile = argv[1];
     fragFile = argv[2];
     modelFile = argv[3];
    }

  // If Argc is 1 then that means there were no arguments given by the user and the program will default to the 2 files in the shaders folder
  else
    {
     vertFile = "vertex.vert";
     fragFile = "fragment.frag";
     modelFile = "test.obj";
    }

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Tutorial Window Name", 800, 600, vertFile, fragFile, modelFile);
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
