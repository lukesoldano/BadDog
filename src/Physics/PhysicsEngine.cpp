#include "PhysicsEngine.hpp"

#include "GameState.hpp"
#include "Logger.hpp"

using namespace Physics;

void PhysicsEngine::initialize()
{
   LOG_MESSAGE("Enter PhysicsEngine::initialize()");

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO Remove
   auto& game_state = GameState::instance();
   for (const auto& entity : game_state.m_active_entities)
   {
      m_spatial_hash_map.add_entity(entity.first, {entity.second.x, entity.second.y});
   }
   for (const auto& entity : game_state.m_static_entities)
   {
      m_spatial_hash_map.add_entity(entity.first, {entity.second.x, entity.second.y});
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
   auto& game_state = GameState::instance();

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO Remove
   Vector2DFloat user_displacement;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::w)]) user_displacement.m_y -= 5.0f;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::a)]) user_displacement.m_x -= 5.0f;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::d)]) user_displacement.m_x += 5.0f;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::s)]) user_displacement.m_y += 5.0f;
   
   game_state.m_active_entities[0].x += user_displacement.m_x;
   game_state.m_active_entities[0].y += user_displacement.m_y;
   m_spatial_hash_map.move_entity(0, { game_state.m_active_entities[0].x, 
                                       game_state.m_active_entities[0].y });
   
   // Broad phase checks
   const auto neighbors = m_spatial_hash_map.get_neighbors(0);

   // Narrow phase checks
   for (const auto& neighbor_id : neighbors)
   {
      if (m_collision_detector.are_aabbs_colliding(game_state.m_active_entities[0],
                                                   game_state.m_static_entities[neighbor_id]))
      {
         game_state.m_active_entities[0].x -= user_displacement.m_x;
         game_state.m_active_entities[0].y -= user_displacement.m_y;
         m_spatial_hash_map.move_entity(0, { game_state.m_active_entities[0].x, 
                                             game_state.m_active_entities[0].y });
      }
   }
   
   /////////////////////////////////////////////////////////////////////////////////////////////////
}