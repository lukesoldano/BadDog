#pragma once

namespace Physics
{

struct Vector2DFloat
{
   float m_x = 0.0f;
   float m_y = 0.0f;

   Vector2DFloat operator+(const Vector2DFloat& rhs) const;
   Vector2DFloat& operator+=(const Vector2DFloat& rhs);
   Vector2DFloat operator-(const Vector2DFloat& rhs) const;
   Vector2DFloat& operator-=(const Vector2DFloat& rhs);
};



} // namespace Physics