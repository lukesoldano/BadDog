#include <gtest/gtest.h>

#include "SpatialHashMap.hpp"

#include <algorithm>
#include <set>

using namespace Physics;

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
}

TEST(SpatialHashMap, GetNeighborsFromCenter) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<5, 5, 100, 100> map;

   // Center entity
   ASSERT_TRUE(map.add_entity(0, {50, 50}).has_value());

   // Expected neighboring entities
   //// Row above 
   ASSERT_TRUE(map.add_entity(1, {30, 30}).has_value());
   ASSERT_TRUE(map.add_entity(2, {50, 30}).has_value());
   ASSERT_TRUE(map.add_entity(3, {70, 30}).has_value());
   //// Same row
   ASSERT_TRUE(map.add_entity(4, {30, 50}).has_value());
   ASSERT_TRUE(map.add_entity(5, {45, 50}).has_value());
   ASSERT_TRUE(map.add_entity(6, {70, 50}).has_value());
   //// Row below 
   ASSERT_TRUE(map.add_entity(7, {30, 70}).has_value());
   ASSERT_TRUE(map.add_entity(8, {50, 70}).has_value());
   ASSERT_TRUE(map.add_entity(9, {70, 70}).has_value());

   // All non-neighboring cells are the borders of the grid, add these
   std::set<EntityId_t> non_neighboring_entities;
   auto current_id = 10;
   for (auto i=0; i<5; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, {10*i, 10}).has_value());
   }

   for (auto i=0; i<5; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, {10*i, 90}).has_value());
   }

   for (auto i=0; i<3; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, {10, 10+20*i}).has_value());
   }

   for (auto i=0; i<3; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, {90, 10+20*i}).has_value());
   }
   
   const auto neighbors = map.get_neighbors(0);
   EXPECT_FALSE(neighbors.empty());

   for (auto i=1; i<10; ++i) EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, i));
   for (const auto& non_neighbor : non_neighboring_entities) 
      EXPECT_EQ(neighbors.end(), std::ranges::find(neighbors, non_neighbor));
}