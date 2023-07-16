#pragma once

#include "ProjectDefs.hpp"

#include "JsonDefs.hpp"

namespace Game
{

struct DogBone
{
   float m_x;
   float m_y;
   float m_scale;
   float m_rotation;

   float get_width() const
   {
      static constexpr float DOG_BONE_WIDTH = 25.0f;
      return m_scale * DOG_BONE_WIDTH;
   }

   float get_height() const
   {
      static constexpr float DOG_BONE_HEIGHT = 25.0f;
      return m_scale * DOG_BONE_HEIGHT;
   }

   FRect get_hitbox() const
   {
      return { m_x, m_y, get_width(), get_height() };
   }

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(DogBone, m_x, m_y, m_scale, m_rotation)
};

} // namespace Game