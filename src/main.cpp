#include "Window.hpp"

#include "GameGraphics.hpp"
#include "Logger.hpp"
#include "GlobalState.hpp"

#include "StdKeyBoardCtrlScheme.hpp"

#include "SDL.h"

#include <math.h>
#include <system_error>

using namespace Graphics;

namespace
{
   // GameInput game_input;
   // GameLogic game_logic;
   GameGraphics game_graphics;
}

int initialize()
{
   // Initialize SDL2
   if (0 != SDL_Init(SDL_INIT_TIMER & SDL_INIT_VIDEO & SDL_INIT_EVENTS & SDL_INIT_GAMECONTROLLER))
   {
      LOG_ERROR("Failed to initialize the SDL2 library, SDL Error: " << SDL_GetError());
      return -1;
   }

   // game_input.initialize();
   // game_logic.initialize();
   game_graphics.initialize();

   return 0;
}

void teardown()
{
   game_graphics.teardown();
   // game_logic.teardown();
   // game_input.teardown();

   SDL_Quit();
}

void run_gameloop()
{
   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO REMOVE THIS  
   GlobalState::Instance().m_current_dog_state.m_theta = 0.0f;
   /////////////////////////////////////////////////////////////////////////////////////////////////

   // @TODO Need to determine how we want to manage game loop timing
   //       https://gameprogrammingpatterns.com/game-loop.html
   // @TODO This will need cleanup, solely using this for demo purposes atm
   auto i = 0;
   auto running = true;
   while (running)
   {
      //////////////////////////////////////////////////////////////////////////////////////////////
      // TODO REMOVE THIS  
      auto& current_dog_state = GlobalState::Instance().m_current_dog_state;
      current_dog_state.m_theta += (180.0f * (1.0f / 50.0f));
      current_dog_state.m_position.x = 340.0f + cos(current_dog_state.m_theta*3.14/180)*170.0f;
      current_dog_state.m_position.y = 360.0f - sin(current_dog_state.m_theta*3.14/180)*180.0f;

      std::cout << "i: " << +i << " theta: " << current_dog_state.m_theta << " x: " << current_dog_state.m_position.x << " y: " << current_dog_state.m_position.y << std::endl;
      //////////////////////////////////////////////////////////////////////////////////////////////

      // game_input.process();
      // game_logic.update();
      game_graphics.render();

      GlobalState::Instance().m_last_dog_state = GlobalState::Instance().m_current_dog_state;

      // Run game for ~5s
      if (i++ < 50)
      {
         SDL_Delay(100);
      }
      else
      {
         running = false;
      }
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