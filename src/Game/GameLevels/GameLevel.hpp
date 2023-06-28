#pragma once

#include "StaticEntity.hpp"

#include <string>
#include <vector>

namespace Game
{

class Level
{
   const std::string m_name;
   const size_t m_width = 0;
   const size_t m_height = 0;
   const size_t m_border_width = 0;

   std::vector<StaticEntity<RectEntity>> m_static_rects;

public:



};

} // namespace Game