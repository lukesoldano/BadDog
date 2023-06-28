#pragma once

#include "GraphicsDefs.hpp"
#include "ProjectDefs.hpp"

namespace Game
{  

enum class StaticEntityType
{
   invalid = -1,
   rect = 0
};

struct RectEntity : public Rect
{
   const Color m_color = Color::white;
};

} // namespace Game