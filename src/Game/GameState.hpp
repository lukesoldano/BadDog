#pragma once

#include "GameSettings.hpp"
#include "ProjectDefs.hpp"
#include "SpatialHashMap.hpp"
#include "UserInputDefs.hpp"

#include <array>
#include <unordered_map>

namespace Game
{

class State
{
public:

   static State& instance()
   {
      static State game_state;
      return game_state;
   }

   // Meta state parameters
   bool m_quit_program = false;

   // User input state parameters, index associated with key enum value
   std::array<bool, static_cast<size_t>(Key::MAX_VALUE)> m_key_pressed{ false };

   // TODO REMOVE - HERE FOR TESTING
   Physics::SpatialHashMap<Settings::DEFAULT_LEVEL_WIDTH, Settings::DEFAULT_LEVEL_HEIGHT, 100, 100> m_spatial_hash_map;

   std::unordered_map<EntityId, FRect> m_active_entities = { {0, {1000.0, 1000.0, 50.0, 50.0}} };
   std::unordered_map<EntityId, FRect> m_static_entities = { 
                                                               {1, {300.0, 100.0, 70.0, 70.0}},
                                                               {2, {200.0, 370.0, 50.0, 75.0}},
                                                               {3, {400.0, 400.0, 50.0, 25.0}},
                                                               {4, {550.0, 400.0, 50.0, 55.0}}
                                                            };

   //

private:

   State() = default; 
   ~State() = default;

};

} // namespace Game