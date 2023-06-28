#include <gtest/gtest.h>

#include "SpatialHashMap.hpp"

using namespace Physics;

TEST(SpatialHashMap, AddEntityNegativeCases) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10> map(100, 100);

   auto entity_cell = map.add_entity(0, {105, 5});
   EXPECT_FALSE(entity_cell.has_value());

   entity_cell = map.add_entity(0, {5, 105});
   EXPECT_FALSE(entity_cell.has_value());

   entity_cell = map.add_entity(0, {105, 105});
   EXPECT_FALSE(entity_cell.has_value());

   // technically width and height are 100, but valid x-y is 0-99
   entity_cell = map.add_entity(0, {100, 100});
   EXPECT_FALSE(entity_cell.has_value());

   // Add valid entity and attempt to re add it to same cell
   entity_cell = map.add_entity(0, {5, 5});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(0, entity_cell.value());

   entity_cell = map.add_entity(0, {5, 5});
   EXPECT_FALSE(entity_cell.has_value());

   // Attempt to add already present entity to new cell
   entity_cell = map.add_entity(0, {35, 35});
   EXPECT_FALSE(entity_cell.has_value());
}

TEST(SpatialHashMap, AddEntityNonBorder) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10> map(100, 100);

   auto entity_cell = map.add_entity(0, {5, 5});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(0, entity_cell.value());

   entity_cell = map.add_entity(1, {15, 5});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(1, entity_cell.value());

   entity_cell = map.add_entity(2, {25, 5});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(2, entity_cell.value());

   entity_cell = map.add_entity(3, {95, 5});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(9, entity_cell.value());

   entity_cell = map.add_entity(4, {5, 15});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(10, entity_cell.value());

   entity_cell = map.add_entity(5, {5, 25});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(20, entity_cell.value());

   entity_cell = map.add_entity(6, {5, 95});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(90, entity_cell.value());

   entity_cell = map.add_entity(7, {55, 55});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(55, entity_cell.value());

   entity_cell = map.add_entity(8, {95, 95});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(99, entity_cell.value());
}

TEST(SpatialHashMap, AddEntityBorder) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<10, 10> map(100, 100);

   auto entity_cell = map.add_entity(0, {0, 0});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(0, entity_cell.value());

   entity_cell = map.add_entity(1, {10, 0});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(1, entity_cell.value());

   entity_cell = map.add_entity(2, {10, 10});
   ASSERT_TRUE(entity_cell.has_value());
   EXPECT_EQ(11, entity_cell.value());
}