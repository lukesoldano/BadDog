#pragma once

#include "StaticEntity.hpp"

#include <string>
#include <vector>

namespace Game
{

class Level
{
public: // TODO UNDO
   const std::string m_name = "default";
   const size_t m_width = 0;
   const size_t m_height = 0;
   const size_t m_border_width = 0;

   std::vector<StaticEntity> m_static_entities;

// public:



};

} // namespace Game