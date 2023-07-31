#include "RgbaColor.hpp"

#include "JSONUtilities.hpp"
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
         ASSERT("Unknown color passed to ColorToRgb switch! Defaulting to black.");
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

void from_json(const nlohmann::json& i_json, RgbaColor& o_color)
{
   using namespace JSON;
   using namespace JSON::Utilities;

   std::string color_str;
   if (get_json_value(i_json, "m_color", color_str))
   {
      auto color = string_to_color(color_str);

      uint8_t alpha;
      if (get_json_value(i_json, "m_alpha", alpha)) o_color = RgbaColor{color, alpha};
      else o_color = RgbaColor{color};
   }
   else
   {
      auto r = i_json.at("m_r").get<uint8_t>();
      auto g = i_json.at("m_g").get<uint8_t>();
      auto b = i_json.at("m_b").get<uint8_t>();

      uint8_t alpha;
      if (get_json_value(i_json, "m_alpha", alpha))
      {
         o_color = RgbaColor{i_json.at("m_r").get<uint8_t>(),
                             i_json.at("m_g").get<uint8_t>(),
                             i_json.at("m_b").get<uint8_t>(), 
                             alpha};
      } 
      else 
      {
         o_color = RgbaColor{i_json.at("m_r").get<uint8_t>(),
                             i_json.at("m_g").get<uint8_t>(),
                             i_json.at("m_b").get<uint8_t>()};
      }
   }

}

void to_json(nlohmann::json& o_json, const RgbaColor& i_color)
{
   o_json["m_r"] = i_color.m_r;
   o_json["m_g"] = i_color.m_g;
   o_json["m_b"] = i_color.m_b;
   o_json["m_a"] = i_color.m_a;
}

RgbaColor::RgbaColor(Color i_color, uint8_t i_alpha) noexcept :
   m_a(i_alpha)
{
   ColorToRgb(i_color, m_r, m_g, m_b);
}

RgbaColor::RgbaColor(uint8_t i_r, uint8_t i_g, uint8_t i_b, uint8_t i_alpha) noexcept :
   m_r(i_r),
   m_g(i_g),
   m_b(i_b),
   m_a(i_alpha)
{

}

bool RgbaColor::operator==(const RgbaColor& i_other) const noexcept
{
   return m_r == i_other.m_r &&
          m_g == i_other.m_g &&
          m_b == i_other.m_b &&
          m_a == i_other.m_a;
}