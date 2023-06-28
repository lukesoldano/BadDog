#pragma once

#include "GameEventTypes.hpp"
#include "ILogicEngine.hpp"
#include "PhysicsEventTypes.hpp"

#include <deque>
#include <functional>

namespace Gameplay
{

// @warning This class is not thread safe
class GameplayEngine : public ILogicEngine
{
   using GameplayEvent = std::function<void()>;

   std::deque<GameplayEvent> m_event_queue;

public:

   GameplayEngine() = default;
   virtual ~GameplayEngine() = default;

   void initialize() override final;
   void teardown() override final;

   void process() override final;

private:

   void subscribe_to_events();
   void unsubscribe_from_events();

   void on_game_loop_elapsed_time(const Game::Event::GameLoopElapsedTime& i_event);
   void on_player_collision_with_static_entity(const Physics::Event::PlayerCollisionWithStaticEntity& i_event);

};

} // namespace Gameplay