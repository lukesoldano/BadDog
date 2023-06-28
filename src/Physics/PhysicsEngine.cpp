#include "PhysicsEngine.hpp"

#include "GameState.hpp"
#include "Logger.hpp"

using namespace Physics;

void PhysicsEngine::initialize()
{
   LOG_MESSAGE("Enter PhysicsEngine::initialize()");

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO Remove
   auto& game_state = Game::State::instance();
   for (const auto& entity : game_state.m_active_entities)
   {
      game_state.m_spatial_hash_map.add_entity(entity.first, entity.second);
   }
   for (const auto& entity : game_state.m_static_entities)
   {
      game_state.m_spatial_hash_map.add_entity(entity.first, entity.second);
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////

   LOG_MESSAGE("Exit PhysicsEngine::initialize()");
}

void PhysicsEngine::teardown()
{
   LOG_MESSAGE("Enter PhysicsEngine::teardown()");

   LOG_MESSAGE("Exit PhysicsEngine::teardown()");
}

void PhysicsEngine::process()
{
   auto& game_state = Game::State::instance();

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO Remove
   Vector2DFloat user_displacement;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::w)]) user_displacement.m_y -= 5.0f;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::a)]) user_displacement.m_x -= 5.0f;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::d)]) user_displacement.m_x += 5.0f;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::s)]) user_displacement.m_y += 5.0f;
   
   if (user_displacement.m_y < 0) game_state.m_player_entity_rotation += 90.0f;
   else if (user_displacement.m_y > 0) game_state.m_player_entity_rotation -= 90.0f;

   if (user_displacement.m_x < 0) game_state.m_player_entity_rotation += 180.0f;

   game_state.m_active_entities[0].x += user_displacement.m_x;
   game_state.m_active_entities[0].y += user_displacement.m_y;
   game_state.m_spatial_hash_map.move_entity(0, game_state.m_active_entities[0]);
   
   // Broad phase checks
   const auto neighbors = game_state.m_spatial_hash_map.get_neighbors(0);

   // Narrow phase checks
   for (const auto& neighbor_id : neighbors)
   {
      if (m_collision_detector.are_aabbs_colliding(game_state.m_active_entities[0],
                                                   game_state.m_static_entities[neighbor_id]))
      {
         game_state.m_active_entities[0].x -= user_displacement.m_x;
         game_state.m_active_entities[0].y -= user_displacement.m_y;
         game_state.m_spatial_hash_map.move_entity(0, game_state.m_active_entities[0]);
      }
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////
}