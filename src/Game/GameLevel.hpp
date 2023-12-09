#pragma once

#include "EntityTypes.hpp"
#include "JsonTypes.hpp"
#include "ProjectTypes.hpp"
#include "SpatialHashMap.hpp"

#include <string>
#include <unordered_map>

namespace Game
{

struct LevelDimmensions
{
   Pixels m_width;
   Pixels m_height;
   Pixels m_border_width;

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(LevelDimmensions, m_width, m_height, m_border_width);
};

struct Level
{
   std::string m_name;

   LevelDimmensions m_dimmensions;

   SpatialHashMap m_spatial_hash_map;

   std::unordered_map<EntityId, std::string> m_named_entities;
   std::unordered_map<EntityId, FPosition> m_positionable_entities;

   void clear()
   {
      *this = Level{};
   }

   void clear_entity(const EntityId& i_id)
   {
      if (m_spatial_hash_map.contains_entity(i_id)) m_spatial_hash_map.remove_entity(i_id);

      m_named_entities.erase(i_id);
      m_positionable_entities.erase(i_id);
   }

};

} // namespace Game