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

   /////////////////////////////////////////////////////////////////////////////////////////////////
   // TODO Remove
   m_player_entity = FRect{ current_level.m_player_start_x, current_level.m_player_start_y, 50.0, 50.0 };
   m_spatial_hash_map.add_entity(PLAYER_ENTITY_ID, m_player_entity);

   // Create border barriers
   static EntityId current_id = 1;
   for (auto i = 0; i < current_level.m_width / current_level.m_shm_cell_width; ++i)
   {
      FRectBarrier border_entity;
      border_entity.m_visible = false;
      border_entity.m_rgba_color = Color::black;
      border_entity.x = (float) i * current_level.m_shm_cell_width;
      border_entity.y = 0.0f;
      border_entity.w = (float) current_level.m_shm_cell_width;
      border_entity.h = (float) current_level.m_border_width;

      m_static_entities.emplace(current_id, StaticEntity{ "x-border", border_entity } );
      m_spatial_hash_map.add_entity(current_id, border_entity);
      ++current_id;

      border_entity.m_visible = false;
      border_entity.m_rgba_color = Color::black;
      border_entity.x = (float) i * current_level.m_shm_cell_width;
      border_entity.y = (float) current_level.m_height - current_level.m_border_width;
      border_entity.w = (float) current_level.m_shm_cell_width;
      border_entity.h = (float) current_level.m_border_width;

      m_static_entities.emplace(current_id, StaticEntity{ "x-border", border_entity });
      m_spatial_hash_map.add_entity(current_id, border_entity);
      ++current_id;
   }

   for (auto i = 0; i < current_level.m_height / current_level.m_shm_cell_height; ++i)
   {
      FRectBarrier border_entity;
      border_entity.m_visible = false;
      border_entity.m_rgba_color = Color::black;
      border_entity.x = 0.0f;
      border_entity.y = (float) i * current_level.m_shm_cell_height;
      border_entity.w = (float) current_level.m_border_width;
      border_entity.h = (float) current_level.m_shm_cell_height;

      m_static_entities.emplace(current_id, StaticEntity{ "y-border", border_entity });
      m_spatial_hash_map.add_entity(current_id, border_entity);
      ++current_id;

      border_entity.m_visible = false;
      border_entity.m_rgba_color = Color::black;
      border_entity.x = (float) current_level.m_width - current_level.m_border_width;
      border_entity.y = (float) i * current_level.m_shm_cell_height;
      border_entity.w = (float) current_level.m_border_width;
      border_entity.h = (float) current_level.m_shm_cell_height;

      m_static_entities.emplace(current_id, StaticEntity{ "y-border", border_entity });
      m_spatial_hash_map.add_entity(current_id, border_entity);
      ++current_id;
   }

   // Add static entities
   for (auto& static_entity : current_level.m_static_entities)
   {
      m_static_entities.emplace(current_id, static_entity);
      m_spatial_hash_map.add_entity(current_id, std::get<FRectBarrier>(static_entity.m_data));
      ++current_id;
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////

   return true;
}

void State::teardown_level() noexcept
{
   if (m_current_level)
   {
      m_current_level.reset();
      m_static_entities.clear();
      m_stationary_dynamic_entities.clear();
      m_mobile_dynamic_entities.clear();
   }
}