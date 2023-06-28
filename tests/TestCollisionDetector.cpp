#include <gtest/gtest.h>

#include "CollisionDetector.hpp"

using namespace Physics;

TEST(CollisionDetector, AABBRectOnRectCollisionOverlap) 
{
   CollisionDetector detector;

   FRect object1{200.0, 200.0, 100.0, 100.0};
   FRect object2 = object1;

   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}

TEST(CollisionDetector, AABBRectOnRectCollisionTop) 
{
   CollisionDetector detector;

   FRect object1{0.0, 0.0, 100.0, 100.0};
   FRect object2{200.0, 200.0, 100.0, 100.0};

   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 200.0;
   object1.y = 100.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 200.0;
   object1.y = 101.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 200.0;
   object1.y = 150.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 200.0;
   object1.y = 175.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}

TEST(CollisionDetector, AABBRectOnRectCollisionBottom) 
{
   CollisionDetector detector;

   FRect object1{0.0, 0.0, 100.0, 100.0};
   FRect object2{200.0, 200.0, 100.0, 100.0};

   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 200.0;
   object1.y = 300.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 200.0;
   object1.y = 299.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 200.0;
   object1.y = 250.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 200.0;
   object1.y = 225.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}

TEST(CollisionDetector, AABBRectOnRectCollisionLeft) 
{
   CollisionDetector detector;

   FRect object1{0.0, 0.0, 100.0, 100.0};
   FRect object2{200.0, 200.0, 100.0, 100.0};

   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 100.0;
   object1.y = 200.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 101.0;
   object1.y = 200.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 150.0;
   object1.y = 200.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 175.0;
   object1.y = 200.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}

TEST(CollisionDetector, AABBRectOnRectCollisionRight) 
{
   CollisionDetector detector;

   FRect object1{0.0, 0.0, 100.0, 100.0};
   FRect object2{200.0, 200.0, 100.0, 100.0};

   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 300.0;
   object1.y = 200.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 299.0;
   object1.y = 200.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 250.0;
   object1.y = 200.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 225.0;
   object1.y = 200.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}

TEST(CollisionDetector, AABBRectOnRectCollisionTopLeft) 
{
   CollisionDetector detector;

   FRect object1{0.0, 0.0, 100.0, 100.0};
   FRect object2{200.0, 200.0, 100.0, 100.0};

   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 100.0;
   object1.y = 100.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 101.0;
   object1.y = 100.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 100.0;
   object1.y = 101.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 150.0;
   object1.y = 100.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));
   
   object1.x = 100.0;
   object1.y = 150.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 100.0;
   object1.y = 200.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 101.0;
   object1.y = 101.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 150.0;
   object1.y = 101.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
   
   object1.x = 101.0;
   object1.y = 150.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}

TEST(CollisionDetector, AABBRectOnRectCollisionBottomLeft) 
{
   CollisionDetector detector;

   FRect object1{0.0, 0.0, 100.0, 100.0};
   FRect object2{200.0, 200.0, 100.0, 100.0};

   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 100.0;
   object1.y = 300.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 101.0;
   object1.y = 300.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 100.0;
   object1.y = 299.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 150.0;
   object1.y = 300.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));
   
   object1.x = 100.0;
   object1.y = 250.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 101.0;
   object1.y = 299.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 150.0;
   object1.y = 299.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
   
   object1.x = 101.0;
   object1.y = 250.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}

TEST(CollisionDetector, AABBRectOnRectCollisionTopRight) 
{
   CollisionDetector detector;

   FRect object1{0.0, 0.0, 100.0, 100.0};
   FRect object2{200.0, 200.0, 100.0, 100.0};

   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 100.0;
   object1.y = 100.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 299.0;
   object1.y = 100.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 300.0;
   object1.y = 101.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 250.0;
   object1.y = 100.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));
   
   object1.x = 300.0;
   object1.y = 150.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 300.0;
   object1.y = 200.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 299.0;
   object1.y = 101.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 250.0;
   object1.y = 101.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
   
   object1.x = 299.0;
   object1.y = 150.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}

TEST(CollisionDetector, AABBRectOnRectCollisionBottomRight) 
{
   CollisionDetector detector;

   FRect object1{0.0, 0.0, 100.0, 100.0};
   FRect object2{200.0, 200.0, 100.0, 100.0};

   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 300.0;
   object1.y = 300.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 299.0;
   object1.y = 300.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 300.0;
   object1.y = 299.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 250.0;
   object1.y = 300.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));
   
   object1.x = 300.0;
   object1.y = 250.0;
   EXPECT_FALSE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_FALSE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 299.0;
   object1.y = 299.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));

   object1.x = 250.0;
   object1.y = 299.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
   
   object1.x = 299.0;
   object1.y = 250.0;
   EXPECT_TRUE(detector.are_aabbs_colliding(object1, object2));
   EXPECT_TRUE(detector.are_aabbs_colliding(object2, object1));
}