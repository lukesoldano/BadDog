#pragma once

// #include "ExtendedOptional.hpp"
// #include "GameLevel.hpp"
// #include "GameSettings.hpp"
// #include "ProjectDefs.hpp"
// #include "SpatialHashMap.hpp"
// #include "UserInputDefs.hpp"

// #include <array>
// #include <unordered_map>

namespace Game
{

class State final
{
//    extended_opt<Level> m_current_level;

public:

   State(const State& i_state) = delete;
   State(State&& i_state) noexcept = default;

   State& operator=(const State& i_state) = delete;
   State& operator=(State&& i_state) noexcept = default;

   inline static State& instance()
   {
      static State game_state;
      return game_state;
   }

//    const extended_opt<Level>& get_level() const noexcept { return m_current_level; }
//    bool load_level(Level&& i_level) noexcept;
//    void teardown_level() noexcept;

   // Meta state parameters
   bool m_quit_program = false;

//    // User input state parameters, index associated with key enum value
//    std::array<bool, static_cast<size_t>(Key::MAX_VALUE)> m_key_pressed{ false };

//    Physics::SpatialHashMap m_spatial_hash_map{1, 1, 1, 1};

//    // TODO REMOVE - HERE FOR TESTING

//    FRect m_player_entity;

//    std::unordered_map<EntityId, StaticEntity> m_static_entities;
//    std::unordered_map<EntityId, StationaryDynamicEntity> m_stationary_dynamic_entities;
//    std::unordered_map<EntityId, FRect> m_mobile_dynamic_entities;

//    float m_player_entity_rotation = 0.0f;

//    double m_remaining_game_time_ms = 10000.0; 

//    //

private:

   State() = default; 
   ~State() = default;

};

} // namespace Game