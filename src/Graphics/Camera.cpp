#include "Camera.hpp"

#include <algorithm>
#include <assert.h>

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
   assert(i_camera_width <= i_level_width);
   assert(i_camera_height <= i_level_height);
}

CameraFrame Camera::get_frame(const SDL_FRect& i_focal_point) const noexcept
{
   CameraFrame o_frame{ {static_cast<int>(i_focal_point.x + (i_focal_point.w / 2.0f)) - (m_camera_width / 2), 
                         static_cast<int>(i_focal_point.y + (i_focal_point.h / 2.0f)) - (m_camera_height / 2), 
                         m_camera_width, 
                         m_camera_height},
                        XFramePosition::off_edge,
                        YFramePosition::off_edge };

   o_frame.m_rect.x = std::clamp(o_frame.m_rect.x, 0, m_level_width - m_camera_width);
   o_frame.m_rect.y = std::clamp(o_frame.m_rect.y, 0, m_level_height - m_camera_height);

   if (0 == o_frame.m_rect.x) o_frame.m_x_frame_position = XFramePosition::on_left_edge;
   else if (m_level_width - m_camera_width == o_frame.m_rect.x) o_frame.m_x_frame_position = XFramePosition::on_right_edge;

   if (0 == o_frame.m_rect.y) o_frame.m_y_frame_position = YFramePosition::on_top_edge;
   else if (m_level_height - m_camera_height == o_frame.m_rect.y) o_frame.m_y_frame_position = YFramePosition::on_bottom_edge;

   return o_frame;
}