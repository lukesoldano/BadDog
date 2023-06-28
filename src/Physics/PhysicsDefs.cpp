#include "PhysicsDefs.hpp"

using namespace Physics;

Vector2DFloat Vector2DFloat::operator+(const Vector2DFloat& rhs) const
{
   return { this->m_x + rhs.m_x, this->m_y + rhs.m_y };
}

Vector2DFloat& Vector2DFloat::operator+=(const Vector2DFloat& rhs)
{
   this->m_x += rhs.m_x;
   this->m_y += rhs.m_y;
   return *this;
}

Vector2DFloat Vector2DFloat::operator-(const Vector2DFloat& rhs) const
{
   return { this->m_x - rhs.m_x, this->m_y - rhs.m_y };
}

Vector2DFloat& Vector2DFloat::operator-=(const Vector2DFloat& rhs)
{
   this->m_x -= rhs.m_x;
   this->m_y -= rhs.m_y;
   return *this;
}