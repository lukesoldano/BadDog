#include "PhysicsEngine.hpp"

#include "GameState.hpp"
#include "Logger.hpp"

using namespace Physics;

void PhysicsEngine::process()
{
   auto& game_state = GameState::instance();

   // TODO Remove
   DisplacementVector_t user_displacement = {0, 0};
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::w)]) user_displacement.second -= 10;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::a)]) user_displacement.first -= 10;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::d)]) user_displacement.first += 10;
   if (game_state.m_key_pressed[static_cast<uint8_t>(Key::s)]) user_displacement.second += 10;
   
   auto collision_position = m_collision_detector.check(game_state.m_player_position,
                                                        game_state.m_obstacle_position,
                                                        user_displacement,
                                                        {0, 0});
   if (!collision_position.has_value())
   {
      game_state.m_player_position.x += user_displacement.first;
      game_state.m_player_position.y += user_displacement.second;
   }
   else
   {
      game_state.m_player_position.x = collision_position.value().first;
      game_state.m_player_position.y = collision_position.value().second;
   }
   //
}