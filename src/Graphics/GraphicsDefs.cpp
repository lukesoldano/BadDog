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
         LOG_WARNING("Unknown color provided, defaulting to black!");
         assert(false && "Unknown color passed to ColorToRgb switch!");
         o_r = 0;
         o_g = 0;
         o_b = 0;
         break;
      }
   }
}

RgbaColor::RgbaColor(Color i_color, uint8_t i_alpha)
{
   ColorToRgb(i_color, m_r, m_g, m_b);
   m_a = i_alpha;
}