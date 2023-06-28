#pragma once

#include "GraphicsDefs.hpp"
#include "ProjectDefs.hpp"
#include "RgbaColor.hpp"

#include "JsonDefs.hpp"

namespace Game
{  

struct RectEntity : public Rect
{
   bool m_visible;
   RgbaColor m_rgba_color;

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(RectEntity, m_visible, m_rgba_color, m_x, m_y, m_w, m_h)
};


} // namespace Game