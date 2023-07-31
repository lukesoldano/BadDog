// #include "GameplayEngine.hpp"

// #include "EventPublisher.hpp"
// #include "GameState.hpp"

// using namespace Gameplay;

// void GameplayEngine::initialize()
// {
//    subscribe_to_events();
// }

// void GameplayEngine::teardown()
// {
//    unsubscribe_from_events();

//    // Depopulate queue
//    m_event_queue.clear();
// }

// void GameplayEngine::subscribe_to_events()
// {
//    using namespace Game::Event;
//    using namespace Physics::Event;

//    M_SUBSCRIBE_TO_EVENT(GameLoopElapsedTime, on_game_loop_elapsed_time);
//    M_SUBSCRIBE_TO_EVENT(PlayerCollisionWithStaticEntity, on_player_collision_with_static_entity);
//    M_SUBSCRIBE_TO_EVENT(PlayerCollisionWithStationaryDynamicEntity, on_player_collision_with_stationary_dynamic_entity);
// }

// void GameplayEngine::unsubscribe_from_events()
// {
//    using namespace Game::Event;
//    using namespace Physics::Event;

//    M_UNSUBSCRIBE_FROM_EVENT(GameLoopElapsedTime);
//    M_UNSUBSCRIBE_FROM_EVENT(PlayerCollisionWithStaticEntity);
//    M_UNSUBSCRIBE_FROM_EVENT(PlayerCollisionWithStationaryDynamicEntity);
// }

// void GameplayEngine::process()
// {
//    while (!m_event_queue.empty())
//    {
//       m_event_queue.front()();
//       m_event_queue.pop_front();
//    }
// }

// void GameplayEngine::on_game_loop_elapsed_time(const Game::Event::GameLoopElapsedTime& i_event)
// {
//    m_event_queue.push_back([i_event]()
//       {
//          auto& game_state = Game::State::instance();

//          game_state.m_remaining_game_time_ms -= i_event.m_elapsed_time_ms;
//          if (game_state.m_remaining_game_time_ms < 0.0)
//          {
//             game_state.m_remaining_game_time_ms = 0.0;
//             // game_state.m_quit_program = true;
//          }

//       });

// }

// void GameplayEngine::on_player_collision_with_static_entity(const Physics::Event::PlayerCollisionWithStaticEntity& i_event)
// {
//    m_event_queue.push_back([i_event]()
//       {
//          auto& game_state = Game::State::instance();
//          LOG_MESSAGE("COLLISION WITH STATIC: " << i_event.m_entity_id);
//       });

// }

// void GameplayEngine::on_player_collision_with_stationary_dynamic_entity(const Physics::Event::PlayerCollisionWithStationaryDynamicEntity& i_event)
// {
//    m_event_queue.push_back([i_event]()
//       {
//          auto& game_state = Game::State::instance();
//          LOG_MESSAGE("COLLISION WITH DYN STATIC: " << i_event.m_entity_id);
//          game_state.m_spatial_hash_map.remove_entity(i_event.m_entity_id);
//          game_state.m_stationary_dynamic_entities.erase(i_event.m_entity_id);
//       });

// }