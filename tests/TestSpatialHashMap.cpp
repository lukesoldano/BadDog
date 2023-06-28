#include <gtest/gtest.h>

#include "SpatialHashMap.hpp"

using namespace Physics;

TEST(SpatialHashMap, AddEntityNegativeCases) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10, 100, 100> map;

   auto cell = map.add_entity(0, {105, 5});
   EXPECT_FALSE(cell.has_value());
   EXPECT_FALSE(map.contains_entity(0));

   cell = map.add_entity(0, {5, 105});
   EXPECT_FALSE(cell.has_value());
   EXPECT_FALSE(map.contains_entity(0));

   cell = map.add_entity(0, {105, 105});
   EXPECT_FALSE(cell.has_value());
   EXPECT_FALSE(map.contains_entity(0));

   // technically width and height are 100, but valid x-y is 0-99
   cell = map.add_entity(0, {100, 100});
   EXPECT_FALSE(cell.has_value());
   EXPECT_FALSE(map.contains_entity(0));

   // Add valid entity and attempt to re add it to same cell
   cell = map.add_entity(0, {5, 5});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.add_entity(0, {5, 5});
   EXPECT_FALSE(cell.has_value());
   EXPECT_TRUE(map.contains_entity(0));

   // Attempt to add already present entity to new cell
   cell = map.add_entity(0, {35, 35});
   EXPECT_FALSE(cell.has_value());
   EXPECT_TRUE(map.contains_entity(0));
}

TEST(SpatialHashMap, AddEntityNonBorderPosition) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10, 100, 100> map;

   auto cell = map.add_entity(0, {5, 5});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.add_entity(1, {15, 5});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(1, cell.value());
   EXPECT_TRUE(map.contains_entity(1));

   cell = map.add_entity(2, {25, 5});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(2, cell.value());
   EXPECT_TRUE(map.contains_entity(2));

   cell = map.add_entity(3, {95, 5});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(9, cell.value());
   EXPECT_TRUE(map.contains_entity(3));

   cell = map.add_entity(4, {5, 15});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(10, cell.value());
   EXPECT_TRUE(map.contains_entity(4));

   cell = map.add_entity(5, {5, 25});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(20, cell.value());
   EXPECT_TRUE(map.contains_entity(5));

   cell = map.add_entity(6, {5, 95});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(90, cell.value());
   EXPECT_TRUE(map.contains_entity(6));

   cell = map.add_entity(7, {55, 55});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(55, cell.value());
   EXPECT_TRUE(map.contains_entity(7));

   cell = map.add_entity(8, {95, 95});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(99, cell.value());
   EXPECT_TRUE(map.contains_entity(8));

   SpatialHashMap<6, 2, 300, 120> mapTwo;
   cell = mapTwo.add_entity(0, {170, 20});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(3, cell.value());
   EXPECT_TRUE(mapTwo.contains_entity(0));

   cell = mapTwo.add_entity(1, {170, 70});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(9, cell.value());
   EXPECT_TRUE(mapTwo.contains_entity(1));
}

TEST(SpatialHashMap, AddEntityBorderPosition) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10, 100, 100> map;

   auto cell = map.add_entity(0, {0, 0});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.add_entity(1, {10, 0});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(1, cell.value());
   EXPECT_TRUE(map.contains_entity(1));

   cell = map.add_entity(2, {10, 10});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(11, cell.value());
   EXPECT_TRUE(map.contains_entity(2));
}

TEST(SpatialHashMap, MoveEntityNegativeCases) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10, 100, 100> map;

   map.add_entity(0, {0, 0});

   ASSERT_TRUE(map.contains_entity(0));

   auto cell = map.move_entity(0, {1000, 0});
   EXPECT_FALSE(cell.has_value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.move_entity(0, {0, 1000});
   EXPECT_FALSE(cell.has_value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.remove_entity(0);
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
}

TEST(SpatialHashMap, MoveEntity) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10, 100, 100> map;

   map.add_entity(0, {0, 0});

   ASSERT_TRUE(map.contains_entity(0));

   auto cell = map.move_entity(0, {5, 5});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.move_entity(0, {35, 75});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(73, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.move_entity(0, {62, 12});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(16, cell.value());
   EXPECT_TRUE(map.contains_entity(0));
}

TEST(SpatialHashMap, RemoveEntityNegativeCases) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10, 100, 100> map;

   EXPECT_FALSE(map.remove_entity(0).has_value());
   EXPECT_FALSE(map.remove_entity(1).has_value());
   EXPECT_FALSE(map.remove_entity(2).has_value());
}

TEST(SpatialHashMap, RemoveEntity) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10, 100, 100> map;

   map.add_entity(0, {0, 0});
   map.add_entity(1, {30, 60});
   map.add_entity(2, {75, 91});

   ASSERT_TRUE(map.contains_entity(0));
   ASSERT_TRUE(map.contains_entity(1));
   ASSERT_TRUE(map.contains_entity(2));

   auto cell = map.remove_entity(0);
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_FALSE(map.contains_entity(0));

   cell = map.remove_entity(1);
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(63, cell.value());
   EXPECT_FALSE(map.contains_entity(1));

   cell = map.remove_entity(2);
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(97, cell.value());
   EXPECT_FALSE(map.contains_entity(2));

   EXPECT_FALSE(map.remove_entity(0).has_value());
   EXPECT_FALSE(map.remove_entity(1).has_value());
   EXPECT_FALSE(map.remove_entity(2).has_value());
}