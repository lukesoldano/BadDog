#include "GameEngine.hpp"

#include "EventPublisher.hpp"
#include "GameEventTypes.hpp"
#include "GameplayEngine.hpp"
#include "GameState.hpp"
#include "Logger.hpp"
#include "PhysicsEngine.hpp"
#include "TestLevel.hpp" // TODO Remove

#include "SDL.h"

#include <math.h>
#include <system_error>

using namespace Game;

using namespace Gameplay;
using namespace Graphics;
using namespace Physics;
using namespace UserInput;

int Engine::initialize()
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
   m_logic_engines.push_back(std::make_unique<GameplayEngine>());
   m_graphics_engine = std::make_unique<GraphicsEngine>();

   m_user_input_engine->initialize();
   for (auto& engine : m_logic_engines) engine->initialize();
   m_graphics_engine->initialize();

   return 0;
}

void Engine::teardown()
{
   m_graphics_engine->teardown();
   for (auto rit = m_logic_engines.rbegin(); rit != m_logic_engines.rend(); ++rit) (*rit)->teardown();
   m_user_input_engine->teardown();

   m_graphics_engine.reset();
   m_logic_engines.clear();
   m_user_input_engine.reset();

   SDL_Quit();
}

void Engine::run_gameloop()
{
   LOG_MESSAGE("Enter Engine::run_gameloop()");

   auto& game_state = State::instance();

   game_state.load_level(TestLevel()); // TODO Remove

   const double DESIRED_MS_PER_FRAME = 1000.0 /*ms*/ / 60.0 /*frame rate*/;

   double loop_end_time = 0.0;
   while (!game_state.m_quit_program)
   {
      const double time_at_loop_start = SDL_GetTicks();

      const auto time_elapsed_ms = time_at_loop_start - loop_end_time;
      EventPublisher::instance().publish_event(Game::Event::GameLoopElapsedTime{time_elapsed_ms});

      m_user_input_engine->process_input();
      for (auto& engine : m_logic_engines) engine->process();
      m_graphics_engine->render();

      loop_end_time = SDL_GetTicks();
      auto sleep_time_ms = time_at_loop_start + DESIRED_MS_PER_FRAME - loop_end_time;
      if (sleep_time_ms > 0.0) SDL_Delay(static_cast<Uint32>(sleep_time_ms));
   }

   LOG_MESSAGE("Exit Engine::run_gameloop()");
} 