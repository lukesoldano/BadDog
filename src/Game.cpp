#include "Game.hpp"

#include "GameState.hpp"
#include "GraphicsEngine.hpp"
#include "Logger.hpp"
#include "PhysicsEngine.hpp"
#include "UserInputEngine.hpp"

#include "SDL.h"

#include <math.h>
#include <system_error>

using namespace Graphics;
using namespace Physics;
using namespace UserInput;

int Game::initialize()
{
   // Initialize SDL2
   if (0 != SDL_Init(SDL_INIT_TIMER & SDL_INIT_VIDEO & SDL_INIT_EVENTS & SDL_INIT_GAMECONTROLLER))
   {
      LOG_ERROR("Failed to initialize the SDL2 library, SDL Error: " << SDL_GetError());
      return -1;
   }

   // Order of engines being added is important here, this is the order to process them in
   m_engines.push_back(std::make_unique<UserInputEngine>());
   m_engines.push_back(std::make_unique<PhysicsEngine>());
   m_engines.push_back(std::make_unique<GraphicsEngine>());

   for (auto& engine : m_engines) engine->initialize();

   return 0;
}

void Game::teardown()
{
   for (auto rit = m_engines.rbegin(); rit != m_engines.rend(); ++rit) (*rit)->teardown();
   m_engines.clear();

   SDL_Quit();
}

void Game::run_gameloop()
{
   LOG_MESSAGE("Enter Game::run_gameloop()");

   auto& game_state = GameState::instance();
   while (!game_state.m_quit_program)
   {
      for (auto& engine : m_engines) engine->process();

      // TODO: Temporary to make framerate near 30 FPS
      SDL_Delay(1000/30);
   }

   LOG_MESSAGE("Exit Game::run_gameloop()");
} 