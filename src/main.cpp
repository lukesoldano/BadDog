#include "GameEngine.hpp"
#include "Logger.hpp"
#include "StaticEntity.hpp"
int main(int argc, char* args[])
{
   LOG_MESSAGE("Enter main()");

   Game::Engine game;
   auto return_value = game.initialize();
   if (0 == return_value) game.run_gameloop();
   game.teardown();

   LOG_MESSAGE("Exit main()");
   return return_value;
}
