#pragma once

#include "JsonTypes.hpp"
#include "ProjectTypes.hpp"
#include "SpatialHashMap.hpp"

#include <string>

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
};

} // namespace Game