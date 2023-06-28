#include "PhysicsEngine.hpp"

#include "GameState.hpp"
#include "Logger.hpp"
#include "SpatialHashMap.hpp"

using namespace Physics;

namespace
{
   SpatialHashMap<5, 5, 680, 480> spatial_hash_map;
}

void PhysicsEngine::process()
{
   auto& game_state = GameState::instance();

   // TODO Remove
   DisplacementVector_t user_displacement = {0, 0};
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::w)]) user_displacement.second -= 10;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::a)]) user_displacement.first -= 10;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::d)]) user_displacement.first += 10;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::s)]) user_displacement.second += 10;
   
   auto collision_position = m_collision_detector.check(game_state.m_active_entities[0],
                                                        game_state.m_static_entities[1]);
   if (!collision_position.has_value())
   {
      game_state.m_active_entities[0].x += user_displacement.first;
      game_state.m_active_entities[0].y += user_displacement.second;
   }
   else
   {
      game_state.m_active_entities[0].x = collision_position.value().x;
      game_state.m_active_entities[0].y = collision_position.value().y;
   }
   //
}