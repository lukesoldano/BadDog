#include <gtest/gtest.h>

#include "Camera.hpp"

using namespace Graphics;

TEST(Camera, GetPosition) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{500.0f, 500.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 325); // (x + w/2) - cam_w/2
   EXPECT_EQ(position.y, 375); // (y + h/2) - cam_h/2

   focal_point = SDL_FRect{320.0f, 740.0f, 50.0f, 25.0f};
   position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 145); // (x + w/2) - cam_w/2
   EXPECT_EQ(position.y, 602); // (y + h/2) - cam_h/2
}

TEST(Camera, GetPositionLeftEdge) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{100.0f, 500.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 0); // clamped
   EXPECT_EQ(position.y, 375); // (y + h/2) - cam_h/2
}

TEST(Camera, GetPositionRightEdge) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{900.0f, 500.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 600); // clamped
   EXPECT_EQ(position.y, 375); // (y + h/2) - cam_h/2
}

TEST(Camera, GetPositionTopEdge) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{500.0f, 100.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 325); // (x + w/2) - cam_w/2
   EXPECT_EQ(position.y, 0); // clamped
}

TEST(Camera, GetPositionBottomEdge) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{500.0f, 900.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 325); // (x + w/2) - cam_w/2
   EXPECT_EQ(position.y, 700); // clamped
}

TEST(Camera, TopLeftCorner) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{100.0f, 100.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 0); // clamped
   EXPECT_EQ(position.y, 0); // clamped
}

TEST(Camera, TopRightCorner) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{900.0f, 100.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 600); // clamped
   EXPECT_EQ(position.y, 0); // clamped
}

TEST(Camera, BottomLeftCorner) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{100.0f, 900.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 0); // clamped
   EXPECT_EQ(position.y, 700); // clamped
}

TEST(Camera, BottomRightCorner) 
{
   Camera camera(400, 300, 1000, 1000);
   SDL_FRect focal_point{900.0f, 900.0f, 50.0f, 50.0f};

   auto position = camera.get_position(focal_point);
   EXPECT_EQ(position.x, 600); // clamped
   EXPECT_EQ(position.y, 700); // clamped
}