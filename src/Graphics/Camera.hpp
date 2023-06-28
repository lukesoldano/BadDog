#pragma once

#include "GameSettings.hpp"

#include <SDL_rect.h>

namespace Graphics
{

class Camera
{
   const int m_camera_width = 0;
   const int m_camera_height = 0;
   const int m_level_width = 0;
   const int m_level_height = 0;

public:

   Camera() = delete;
   Camera(size_t i_camera_width, 
          size_t i_camera_height, 
          size_t i_level_width, 
          size_t i_level_height);
   virtual ~Camera() = default;

   SDL_Rect get_position(const SDL_FRect& i_focal_point) const noexcept;

};

}