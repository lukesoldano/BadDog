#include "Game.hpp"

#include "GameState.hpp"
#include "Logger.hpp"
#include "PhysicsEngine.hpp"

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
   m_user_input_engine = std::make_unique<UserInputEngine>();
   m_logic_engines.push_back(std::make_unique<PhysicsEngine>());
   m_graphics_engine = std::make_unique<GraphicsEngine>();

   m_user_input_engine->initialize();
   for (auto& engine : m_logic_engines) engine->initialize();
   m_graphics_engine->initialize();

   return 0;
}

void Game::teardown()
{
   m_graphics_engine->teardown();
   for (auto rit = m_logic_engines.rbegin(); rit != m_logic_engines.rend(); ++rit) (*rit)->teardown();
   m_user_input_engine->teardown();

   m_graphics_engine.reset();
   m_logic_engines.clear();
   m_user_input_engine.reset();

   SDL_Quit();
}

void Game::run_gameloop()
{
   LOG_MESSAGE("Enter Game::run_gameloop()");

   auto& game_state = GameState::instance();

   const double DESIRED_MS_PER_FRAME = 1000.0 /*ms*/ / 60.0 /*frame rate*/;

   while (!game_state.m_quit_program)
   {
      const double time_at_loop_start = SDL_GetTicks();

      m_user_input_engine->process_input();
      for (auto& engine : m_logic_engines) engine->process();
      m_graphics_engine->render();

      auto sleep_time_ms = time_at_loop_start + DESIRED_MS_PER_FRAME - double(SDL_GetTicks());
      if (sleep_time_ms > 0.0) SDL_Delay(static_cast<Uint32>(sleep_time_ms));
   }

   LOG_MESSAGE("Exit Game::run_gameloop()");
} 