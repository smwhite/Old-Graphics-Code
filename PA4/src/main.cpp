#include <iostream>

#include "engine.h"


int main(int argc, char **argv)
{
  // Start an engine and run it then cleanup after
  //std::cout<<argv[1]<<"   main"<<std::endl;
  Engine *engine = new Engine("Tutorial Window Name", 800, 600,argv[1]);
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