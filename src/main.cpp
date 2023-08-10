#include "GameEngine.hpp"
#include "Logger.hpp"

int main(int argc, char* args[])
{
   LOG_MESSAGE("Enter main()");

   auto& game = Game::Engine::instance();
   
   if (game.initialize()) game.run_gameloop();
   game.teardown();

   LOG_MESSAGE("Exit main()");

   return 0;
}
