#include <gtest/gtest.h>

#include "Camera.hpp"

using namespace Graphics;

TEST(Camera, GetPosition) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{500.0f, 500.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 325); // (x + w/2) - cam_w/2
   EXPECT_EQ(frame.m_level_position.to_rect().y, 375); // (y + h/2) - cam_h/2
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::off_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::off_edge);

   focal_point = FRect{320.0f, 740.0f, 50.0f, 25.0f};
   frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 145); // (x + w/2) - cam_w/2
   EXPECT_EQ(frame.m_level_position.to_rect().y, 603); // (y + h/2) - cam_h/2
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::off_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::off_edge);
}

TEST(Camera, GetPositionLeftEdge) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{100.0f, 500.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 0); // clamped
   EXPECT_EQ(frame.m_level_position.to_rect().y, 375); // (y + h/2) - cam_h/2
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::on_left_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::off_edge);
}

TEST(Camera, GetPositionRightEdge) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{900.0f, 500.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 600); // clamped
   EXPECT_EQ(frame.m_level_position.to_rect().y, 375); // (y + h/2) - cam_h/2
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::on_right_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::off_edge);
}

TEST(Camera, GetPositionTopEdge) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{500.0f, 100.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 325); // (x + w/2) - cam_w/2
   EXPECT_EQ(frame.m_level_position.to_rect().y, 0); // clamped
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::off_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::on_top_edge);
}

TEST(Camera, GetPositionBottomEdge) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{500.0f, 900.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 325); // (x + w/2) - cam_w/2
   EXPECT_EQ(frame.m_level_position.to_rect().y, 700); // clamped
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::off_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::on_bottom_edge);
}

TEST(Camera, TopLeftCorner) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{100.0f, 100.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 0); // clamped
   EXPECT_EQ(frame.m_level_position.to_rect().y, 0); // clamped
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::on_left_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::on_top_edge);
}

TEST(Camera, TopRightCorner) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{900.0f, 100.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 600); // clamped
   EXPECT_EQ(frame.m_level_position.to_rect().y, 0); // clamped
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::on_right_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::on_top_edge);
}

TEST(Camera, BottomLeftCorner) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{100.0f, 900.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 0); // clamped
   EXPECT_EQ(frame.m_level_position.to_rect().y, 700); // clamped
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::on_left_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::on_bottom_edge);
}

TEST(Camera, BottomRightCorner) 
{
   Camera camera(400, 300, 1000, 1000);
   FRect focal_point{900.0f, 900.0f, 50.0f, 50.0f};

   auto frame = camera.get_frame(focal_point);
   EXPECT_EQ(frame.m_level_position.to_rect().x, 600); // clamped
   EXPECT_EQ(frame.m_level_position.to_rect().y, 700); // clamped
   EXPECT_EQ(frame.m_x_frame_position, XFramePosition::on_right_edge);
   EXPECT_EQ(frame.m_y_frame_position, YFramePosition::on_bottom_edge);
}