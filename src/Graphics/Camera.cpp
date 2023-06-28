#include "Camera.hpp"

#include <algorithm>

using namespace Graphics;

Camera::Camera(size_t i_camera_width, 
               size_t i_camera_height, 
               size_t i_level_width, 
               size_t i_level_height) :
   m_camera_width(static_cast<int>(i_camera_width)),
   m_camera_height(static_cast<int>(i_camera_height)),
   m_level_width(static_cast<int>(i_level_width)),
   m_level_height(static_cast<int>(i_level_height))
{

}

SDL_Rect Camera::get_position(const SDL_FRect& i_focal_point) const noexcept
{
   SDL_Rect o_position{static_cast<int>(i_focal_point.x + (i_focal_point.w / 2.0f)) - (m_camera_width / 2), 
                       static_cast<int>(i_focal_point.y + (i_focal_point.h / 2.0f)) - (m_camera_height / 2), 
                       m_camera_width, 
                       m_camera_height};

   o_position.x = std::clamp(o_position.x, 0, m_level_width - m_camera_width);
   o_position.y = std::clamp(o_position.y, 0, m_level_height - m_camera_height);

   return o_position;
}