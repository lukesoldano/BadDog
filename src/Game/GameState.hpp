#pragma once

#include "ExtendedOptional.hpp"
#include "GameLevel.hpp"
#include "GameSettings.hpp"
#include "ProjectDefs.hpp"
#include "SpatialHashMap.hpp"
#include "UserInputDefs.hpp"

#include <array>
#include <unordered_map>

namespace Game
{

// @warning This class is not thread safe
class State final
{
   extended_opt<Level> m_current_level;

public:

   State(const State& i_state) = delete;
   State(State&& i_state) noexcept = default;

   State& operator=(const State& i_state) = delete;
   State& operator=(State&& i_state) noexcept = default;

   static State& instance()
   {
      static State game_state;
      return game_state;
   }

   const extended_opt<Level>& get_level() const noexcept { return m_current_level; }
   bool load_level(Level&& i_level) noexcept;
   void teardown_level() noexcept;

   // Meta state parameters
   bool m_quit_program = false;

   // User input state parameters, index associated with key enum value
   std::array<bool, static_cast<size_t>(Key::MAX_VALUE)> m_key_pressed{ false };

   Physics::SpatialHashMap m_spatial_hash_map{1, 1, 1, 1};

   // TODO REMOVE - HERE FOR TESTING

   std::unordered_map<EntityId, FRect> m_active_entities;
   std::unordered_map<EntityId, FRectEntity> m_static_entities;

   float m_player_entity_rotation = 0.0f;

   //

private:

   State() noexcept = default; 
   ~State() noexcept = default;

};

} // namespace Game