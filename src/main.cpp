#include "Window.hpp"

#include "GameState.hpp"
#include "GraphicsEngine.hpp"
#include "Logger.hpp"
#include "UserInputEngine.hpp"

#include "SDL.h"

#include <math.h>
#include <system_error>

using namespace Graphics;
using namespace UserInput;

namespace
{
   GraphicsEngine graphics_engine;
   UserInputEngine user_input_engine;
}

int initialize()
{
   // Initialize SDL2
   if (0 != SDL_Init(SDL_INIT_TIMER & SDL_INIT_VIDEO & SDL_INIT_EVENTS & SDL_INIT_GAMECONTROLLER))
   {
      LOG_ERROR("Failed to initialize the SDL2 library, SDL Error: " << SDL_GetError());
      return -1;
   }

   graphics_engine.initialize();
   user_input_engine.initialize();

   return 0;
}

void teardown()
{
   // Tearing down in reverse order
   user_input_engine.teardown();
   graphics_engine.teardown();

   SDL_Quit();
}

void run_gameloop()
{
   // @TODO Need to determine how we want to manage game loop timing
   //       https://gameprogrammingpatterns.com/game-loop.html
   while (!GameState::Instance().m_quit_program)
   {
      user_input_engine.process();
      graphics_engine.render();
   }
}

int main(int argc, char* args[])
{
   LOG_MESSAGE("Enter main()");

   auto return_value = initialize();
   if (0 == return_value) run_gameloop();
   teardown();

   LOG_MESSAGE("Exit main()");
   return return_value;
}