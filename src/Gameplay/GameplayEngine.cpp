#include "GameplayEngine.hpp"

#include "EventPublisher.hpp"
#include "GameState.hpp"

using namespace Gameplay;

void GameplayEngine::initialize()
{
   subscribe_to_events();
}

void GameplayEngine::teardown()
{
   unsubscribe_from_events();

   // Depopulate queue
   m_event_queue.clear();
}

void GameplayEngine::subscribe_to_events()
{
   using namespace Game::Event;
   using namespace Physics::Event;

   M_SUBSCRIBE_TO_EVENT(GameLoopElapsedTime, on_game_loop_elapsed_time);
   M_SUBSCRIBE_TO_EVENT(PlayerCollisionWithStaticEntity, on_player_collision_with_static_entity);
}

void GameplayEngine::unsubscribe_from_events()
{
   using namespace Game::Event;
   using namespace Physics::Event;

   M_UNSUBSCRIBE_FROM_EVENT(GameLoopElapsedTime);
}

void GameplayEngine::process()
{
   while (!m_event_queue.empty())
   {
      m_event_queue.front()();
      m_event_queue.pop_front();
   }
}

void GameplayEngine::on_game_loop_elapsed_time(const Game::Event::GameLoopElapsedTime& i_event)
{
   m_event_queue.push_back([i_event]()
      {
         auto& game_state = Game::State::instance();

         game_state.m_remaining_game_time_ms -= i_event.m_elapsed_time_ms;
         if (game_state.m_remaining_game_time_ms < 0.0)
         {
            game_state.m_remaining_game_time_ms = 0.0;
            // game_state.m_quit_program = true;
         }

      });

}

void GameplayEngine::on_player_collision_with_static_entity(const Physics::Event::PlayerCollisionWithStaticEntity& i_event)
{
   m_event_queue.push_back([i_event]()
      {
         auto& game_state = Game::State::instance();
         LOG_MESSAGE("COLLISION WITH: " << i_event.m_static_entity_id);
      });

}