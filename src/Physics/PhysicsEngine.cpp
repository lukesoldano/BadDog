#include "PhysicsEngine.hpp"

#include "GameState.hpp"
#include "Logger.hpp"
#include "SpatialHashMap.hpp"

using namespace Physics;

namespace
{
   SpatialHashMap<7, 5, 700, 500> spatial_hash_map;
}

void PhysicsEngine::initialize()
{
   LOG_MESSAGE("Enter PhysicsEngine::initialize()");

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO Remove
   auto& game_state = GameState::instance();
   for (const auto& entity : game_state.m_active_entities)
   {
      spatial_hash_map.add_entity(entity.first, {entity.second.x, entity.second.y});
   }
   for (const auto& entity : game_state.m_static_entities)
   {
      spatial_hash_map.add_entity(entity.first, {entity.second.x, entity.second.y});
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
   Vector2DFloat_t user_displacement = { 0.0, 0.0 };
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::w)]) user_displacement.second -= 10.0;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::a)]) user_displacement.first -= 10.0;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::d)]) user_displacement.first += 10.0;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::s)]) user_displacement.second += 10.0;
   
   // auto collision_position = m_collision_detector.check(game_state.m_active_entities[0],
   //                                                      game_state.m_static_entities[1]);
   // if (!collision_position.has_value())
   // {
   game_state.m_active_entities[0].x += user_displacement.first;
   game_state.m_active_entities[0].y += user_displacement.second;
   spatial_hash_map.move_entity(0, { game_state.m_active_entities[0].x, 
                                     game_state.m_active_entities[0].y });
   // }
   // else
   // {
   //    game_state.m_active_entities[0].x = collision_position.value().x;
   //    game_state.m_active_entities[0].y = collision_position.value().y;
   // }
   
   // Broad phase checks
   const auto neighbors = spatial_hash_map.get_neighbors(0);

   // Narrow phase checks
   
   
   /////////////////////////////////////////////////////////////////////////////////////////////////
}