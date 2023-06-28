#include "GameState.hpp"

using namespace Game;

bool State::load_level(Level&& i_level) noexcept
{
   if (m_current_level) teardown_level();
   m_current_level = std::move(i_level);

   auto& current_level = m_current_level.value();

   m_spatial_hash_map = Physics::SpatialHashMap{ current_level.m_width, 
                                                 current_level.m_height, 
                                                 current_level.m_shm_cell_width, 
                                                 current_level.m_shm_cell_height };

   // TODO Remove
   m_active_entities.emplace(0, FRect{ current_level.m_player_start_x, current_level.m_player_start_y, 50.0, 50.0 });
   m_spatial_hash_map.add_entity(0, FRect{ current_level.m_player_start_x, current_level.m_player_start_y, 50.0, 50.0 });

   static EntityId current_id = 1;
   for (auto& static_entity : current_level.m_static_entities)
   {
      m_static_entities.emplace(current_id, std::get<FRectEntity>(static_entity.m_data));
      m_spatial_hash_map.add_entity(current_id, std::get<FRectEntity>(static_entity.m_data));
      ++current_id;
   }
   //

   return true;
}

void State::teardown_level() noexcept
{
   if (m_current_level)
   {
      m_current_level.reset();
      m_active_entities.clear();
      m_static_entities.clear();
   }
}