#include "GameEngine.hpp"

#include "EventPublisher.hpp"
// #include "GameplayEngine.hpp"
#include "GameState.hpp"
#include "GraphicsEngine.hpp"
#include "Logger.hpp"
// #include "PhysicsEngine.hpp"
#include "UserInputEngine.hpp"

#include "SDL.h"

#include <math.h>
#include <system_error>

using namespace Game;

bool Engine::initialize()
{
   // Initialize SDL2
   if (0 != SDL_Init(SDL_INIT_TIMER & SDL_INIT_VIDEO & SDL_INIT_EVENTS & SDL_INIT_GAMECONTROLLER))
   {
      ASSERT(std::string("Failed to initialize the SDL2 library, SDL Error: ") + SDL_GetError());
      return false;
   }

   // Event subscriptions
   M_SUBSCRIBE_TO_EVENT(Events::QuitProgramRequested, on_quit_requested);

   // Order of engines being added is important here, this is the order to process them in
   m_sub_engines.emplace_back(std::make_unique<UserInput::Engine>());
   // m_sub_engines.push_back(std::make_unique<PhysicsEngine>());
   // m_sub_engines.push_back(std::make_unique<GameplayEngine>());
   m_sub_engines.emplace_back(std::make_unique<Graphics::Engine>());

   for (auto& engine : m_sub_engines) engine->initialize();

   return true;
}

bool Engine::teardown()
{
   // Teardown engines in reverse order of initialization
   for (auto rit = m_sub_engines.rbegin(); rit != m_sub_engines.rend(); ++rit) (*rit)->teardown();

   m_sub_engines.clear();

   // Event unsubscriptions
   M_UNSUBSCRIBE_FROM_EVENT(Events::QuitProgramRequested);

   SDL_Quit();

   return true;
}

void Engine::on_quit_requested(const Events::QuitProgramRequested& i_event)
{
   LOG_MESSAGE("User has incited a program quit!");
   auto& game_state = State::instance().m_quit_program = true;
}

void Engine::run_gameloop()
{
   LOG_MESSAGE("Enter run_gameloop()");

   auto& game_state = State::instance();

//    game_state.load_level(TestLevel()); // TODO Remove

   const double DESIRED_MS_PER_FRAME = 1000.0 /*ms*/ / 60.0 /*frame rate*/;

   double loop_end_time = 0.0;
   while (!game_state.m_quit_program)
   {
      const double time_at_loop_start = SDL_GetTicks();

      const auto time_elapsed_ms = time_at_loop_start - loop_end_time;
//       EventPublisher::instance().publish_event(Game::Event::GameLoopElapsedTime{time_elapsed_ms});

      for (auto& engine : m_sub_engines) engine->process();

      loop_end_time = SDL_GetTicks();
      auto sleep_time_ms = time_at_loop_start + DESIRED_MS_PER_FRAME - loop_end_time;
      if (sleep_time_ms > 0.0) SDL_Delay(static_cast<Uint32>(sleep_time_ms));
   }

   LOG_MESSAGE("Exit run_gameloop()");
} 