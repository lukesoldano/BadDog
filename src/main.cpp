#include "Game.hpp"
#include "Logger.hpp"

int main(int argc, char* args[])
{
   LOG_MESSAGE("Enter main()");

   Game game;
   auto return_value = game.initialize();
   if (0 == return_value) game.run_gameloop();
   game.teardown();

   LOG_MESSAGE("Exit main()");
   return return_value;
}