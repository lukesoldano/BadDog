#pragma once

#include "JSONDefs.hpp"

#include <stdint.h>
#include <string>

// @note This list is not obviously all encompassing for the color spectrum, feel free to add colors
enum class Color
{
   invalid = -1,
   black = 0,
   white = 1,
   red = 2,
   lime = 3,
   blue = 4,
   yellow = 5,
   cyan = 6,
   magenta = 7,
   silver = 8,
   grey = 9,
   maroon = 10,
   olive = 11,
   green = 12,
   purple = 13,
   teal = 14,
   navy = 15
};

Color string_to_color(const std::string& i_color) noexcept;

struct RgbaColor
{
   uint8_t m_r = 0;
   uint8_t m_g = 0;
   uint8_t m_b = 0;
   uint8_t m_a = 255; // 0 = transparent, 255 = opaque

   RgbaColor() = default;
   RgbaColor(Color i_color, uint8_t i_alpha = 255) noexcept;
   RgbaColor(uint8_t i_r, uint8_t i_g, uint8_t i_b, uint8_t i_alpha = 255) noexcept;

   bool operator==(const RgbaColor& i_other) const noexcept;
};

void from_json(const nlohmann::json& i_json, RgbaColor& o_color);
void to_json(nlohmann::json& o_json, const RgbaColor& i_color);