// #include "PhysicsEngine.hpp"

// #include "EventPublisher.hpp"
// #include "GameState.hpp"
// #include "Logger.hpp"
// #include "PhysicsEventTypes.hpp"

// using namespace Physics;
// using namespace Physics::Event;

// void PhysicsEngine::initialize()
// {
//    LOG_MESSAGE("Enter PhysicsEngine::initialize()");

//    LOG_MESSAGE("Exit PhysicsEngine::initialize()");
// }

// void PhysicsEngine::teardown()
// {
//    LOG_MESSAGE("Enter PhysicsEngine::teardown()");

//    LOG_MESSAGE("Exit PhysicsEngine::teardown()");
// }

// void PhysicsEngine::process()
// {
//    auto& game_state = Game::State::instance();

//    /////////////////////////////////////////////////////////////////////////////////////////////////
//    // TODO Remove
//    Vector2DFloat user_displacement;
//    if (game_state.m_key_pressed[static_cast<uint8_t>(Key::w)]) user_displacement.m_y -= 5.0f;
//    if (game_state.m_key_pressed[static_cast<uint8_t>(Key::a)]) user_displacement.m_x -= 5.0f;
//    if (game_state.m_key_pressed[static_cast<uint8_t>(Key::d)]) user_displacement.m_x += 5.0f;
//    if (game_state.m_key_pressed[static_cast<uint8_t>(Key::s)]) user_displacement.m_y += 5.0f;
   
//    if (user_displacement.m_y < 0) game_state.m_player_entity_rotation += 90.0f;
//    else if (user_displacement.m_y > 0) game_state.m_player_entity_rotation -= 90.0f;

//    if (user_displacement.m_x < 0) game_state.m_player_entity_rotation += 180.0f;

//    game_state.m_player_entity.x += user_displacement.m_x;
//    game_state.m_player_entity.y += user_displacement.m_y;
//    auto player_entity = game_state.m_player_entity;
//    //game_state.m_spatial_hash_map.move_entity(Game::PLAYER_ENTITY_ID, game_state.m_player_entity);
//    game_state.m_spatial_hash_map.move_entity(Game::PLAYER_ENTITY_ID, std::move(player_entity));
   
//    // Broad phase checks
//    const auto neighbors = game_state.m_spatial_hash_map.get_neighbors(Game::PLAYER_ENTITY_ID);

//    // Narrow phase checks
//    for (const auto& neighbor_id : neighbors)
//    {
//       if (game_state.m_static_entities.contains(neighbor_id) &&
//           m_collision_detector.are_aabbs_colliding(game_state.m_player_entity,
//                                                    game_state.m_static_entities[neighbor_id].get_hitbox()))
//       {
//          game_state.m_player_entity.x -= user_displacement.m_x;
//          game_state.m_player_entity.y -= user_displacement.m_y;
//          game_state.m_spatial_hash_map.move_entity(Game::PLAYER_ENTITY_ID, game_state.m_player_entity);
//          EventPublisher::instance().publish_event(PlayerCollisionWithStaticEntity{ neighbor_id });
//       }
//       else if (game_state.m_stationary_dynamic_entities.contains(neighbor_id) &&
//                m_collision_detector.are_aabbs_colliding(game_state.m_player_entity,
//                                                         game_state.m_stationary_dynamic_entities[neighbor_id].get_hitbox()))
//       {
//          EventPublisher::instance().publish_event(PlayerCollisionWithStationaryDynamicEntity{ neighbor_id });
//       }
//    }
   
//    /////////////////////////////////////////////////////////////////////////////////////////////////
// }