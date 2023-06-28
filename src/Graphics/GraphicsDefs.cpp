#include "GraphicsDefs.hpp"

#include "Logger.hpp"

#include <assert.h>

namespace
{
   void ColorToRgb(Color i_color, uint8_t& o_r, uint8_t& o_g, uint8_t& o_b)
   {
      switch (i_color)
      {
      case Color::black: 
         o_r = 0;
         o_g = 0;
         o_b = 0;
         break;
      case Color::white:
         o_r = 255;
         o_g = 255;
         o_b = 255;
         break;
      case Color::red:
         o_r = 255;
         o_g = 0;
         o_b = 0;
         break;
      case Color::lime:
         o_r = 0;
         o_g = 255;
         o_b = 0;
         break;
      case Color::blue:
         o_r = 0;
         o_g = 0;
         o_b = 255;
         break;
      case Color::yellow:
         o_r = 255;
         o_g = 255;
         o_b = 0;
         break;
      case Color::cyan:
         o_r = 0;
         o_g = 255;
         o_b = 255;
         break;
      case Color::magenta:
         o_r = 255;
         o_g = 0;
         o_b = 255;
         break;
      case Color::silver:
         o_r = 192;
         o_g = 192;
         o_b = 192;
         break;
      case Color::grey:
         o_r = 128;
         o_g = 128;
         o_b = 128;
         break;
      case Color::maroon:
         o_r = 128;
         o_g = 0;
         o_b = 0;
         break;
      case Color::olive:
         o_r = 128;
         o_g = 128;
         o_b = 0;
         break;
      case Color::green:
         o_r = 0;
         o_g = 128;
         o_b = 0;
         break;
      case Color::purple:
         o_r = 128;
         o_g = 0;
         o_b = 128;
         break;
      case Color::teal:
         o_r = 0;
         o_g = 128;
         o_b = 128;
         break;
      case Color::navy:
         o_r = 0;
         o_g = 0;
         o_b = 128;
         break;
      default:
         assert(false && "Unknown color passed to ColorToRgb switch!");
         LOG_WARNING("Unknown color provided, defaulting to black!");
         o_r = 0;
         o_g = 0;
         o_b = 0;
         break;
      }
   }

} // namespace

Color string_to_color(const std::string& i_color) noexcept
{
   if ("black" == i_color) return Color::black;
   else if ("white" == i_color) return Color::white;
   else if ("red" == i_color) return Color::red;
   else if ("lime" == i_color) return Color::lime;
   else if ("blue" == i_color) return Color::blue;
   else if ("yellow" == i_color) return Color::yellow;
   else if ("cyan" == i_color) return Color::cyan;
   else if ("magenta" == i_color) return Color::magenta;
   else if ("silver" == i_color) return Color::silver;
   else if ("grey" == i_color) return Color::grey;
   else if ("maroon" == i_color) return Color::maroon;
   else if ("olive" == i_color) return Color::olive;
   else if ("green" == i_color) return Color::green;
   else if ("purple" == i_color) return Color::purple;
   else if ("teal" == i_color) return Color::teal;
   else if ("navy" == i_color) return Color::navy;

   return Color::invalid;
}

RgbaColor::RgbaColor(Color i_color, uint8_t i_alpha) noexcept
{
   ColorToRgb(i_color, m_r, m_g, m_b);
   m_a = i_alpha;
}