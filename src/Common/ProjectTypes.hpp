#pragma once

#include <cstdint>

using Pixels = int;
using FPixels = float;

struct FPosition;

struct Position
{
   Pixels m_x;
   Pixels m_y;

   FPosition to_fposition() const;
};

struct FPosition
{
   FPixels m_x;
   FPixels m_y;

   Position to_position() const;
};

struct Rect
{
   Pixels m_width;
   Pixels m_height;
};

struct FRect
{
   FPixels m_width;
   FPixels m_height;
};