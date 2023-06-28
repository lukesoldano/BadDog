#pragma once

#include "GraphicsDefs.hpp"
#include "ProjectDefs.hpp"

namespace Game
{  

struct RectEntity : public Rect
{
   const Color m_color = Color::white;

   RectEntity() = default;
   RectEntity(Color i_color, 
              Rect&& i_rect) noexcept : 
      Rect(std::move(i_rect)), 
      m_color(i_color) {}

};

} // namespace Game