// #include "Camera.hpp"

// #include <algorithm>

// using namespace Graphics;

// Camera::Camera(size_t i_camera_width, 
//                size_t i_camera_height, 
//                size_t i_level_width, 
//                size_t i_level_height) :
//    m_camera_width(static_cast<int>(i_camera_width)),
//    m_camera_height(static_cast<int>(i_camera_height)),
//    m_level_width(static_cast<int>(i_level_width)),
//    m_level_height(static_cast<int>(i_level_height))
// {
//    assert(i_camera_width <= i_level_width);
//    assert(i_camera_height <= i_level_height);
// }

// CameraFrame Camera::get_frame(const FRect& i_focal_point) const noexcept
// {
//    CameraFrame o_frame{ {(i_focal_point.x + (i_focal_point.w / 2.0f)) - (m_camera_width / 2.0f), 
//                          (i_focal_point.y + (i_focal_point.h / 2.0f)) - (m_camera_height / 2.0f), 
//                          (float) m_camera_width, 
//                          (float) m_camera_height},
//                         XFramePosition::off_edge,
//                         YFramePosition::off_edge };

//    if (0.0f >= o_frame.m_level_position.x)
//    {
//       o_frame.m_level_position.x = 0.0f;
//       o_frame.m_x_frame_position = XFramePosition::on_left_edge;
//    }
//    else if ((float)(m_level_width - m_camera_width) <= o_frame.m_level_position.x)
//    {
//       o_frame.m_level_position.x = m_level_width - m_camera_width;
//       o_frame.m_x_frame_position = XFramePosition::on_right_edge;
//    }

//    if (0.0f >= o_frame.m_level_position.y)
//    {
//       o_frame.m_level_position.y = 0.0f;
//       o_frame.m_y_frame_position = YFramePosition::on_top_edge;
//    }
//    else if ((float)(m_level_height - m_camera_height) <= o_frame.m_level_position.y)
//    {
//       o_frame.m_level_position.y = m_level_height - m_camera_height;
//       o_frame.m_y_frame_position = YFramePosition::on_bottom_edge;
//    }

//    return o_frame;
// }