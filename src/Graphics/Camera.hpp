#pragma once

#include "GameSettings.hpp"

#include <SDL_rect.h>

namespace Graphics
{

enum class XFramePosition
{
   off_edge = 0,
   on_left_edge = 1,
   on_right_edge = 2
};

enum class YFramePosition
{
   off_edge = 0,
   on_top_edge = 1,
   on_bottom_edge = 2
};

struct CameraFrame
{
   SDL_Rect m_rect;
   XFramePosition m_x_frame_position;
   YFramePosition m_y_frame_position;
};

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

   CameraFrame get_frame(const SDL_FRect& i_focal_point) const noexcept;

};

}