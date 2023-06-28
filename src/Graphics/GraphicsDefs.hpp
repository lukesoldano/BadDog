#pragma once

#include "SDL_render.h"

#include <functional>
#include <stdint.h>

using RenderInstruction_t = std::function<bool(SDL_Renderer&)>;

// @note This list is not obviously all encompassing for the color spectrum, feel free to add colors
enum class Color
{
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

struct RgbaColor
{
   RgbaColor() = default;
   RgbaColor(Color color, uint8_t alpha = 255);

   uint8_t m_r;
   uint8_t m_g;
   uint8_t m_b;
   uint8_t m_a; // 0 = transparent, 255 = opaque
};
