#include "ProjectTypes.hpp"

#include <cmath>

FPosition Position::to_fposition() const
{
   return FPosition{ static_cast<FPixels>(m_x), static_cast<FPixels>(m_y) };
}

Position FPosition::to_position() const
{
   return Position{std::lround(m_x), std::lround(m_y)};
}