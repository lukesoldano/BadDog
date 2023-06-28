#include <gtest/gtest.h>

#include "SpatialHashMap.hpp"

#include <algorithm>
#include <set>

using namespace Physics;

TEST(SpatialHashMap, AddEntityNonBorderPosition) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<100, 100, 10, 10> map;

   auto cell = map.add_entity(0, FPoint{5.0f, 5.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.add_entity(1, FPoint{15.0f, 5.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(1, cell.value());
   EXPECT_TRUE(map.contains_entity(1));

   cell = map.add_entity(2, FPoint{25.0f, 5.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(2, cell.value());
   EXPECT_TRUE(map.contains_entity(2));

   cell = map.add_entity(3, FPoint{95.0f, 5.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(9, cell.value());
   EXPECT_TRUE(map.contains_entity(3));

   cell = map.add_entity(4, FPoint{5.0f, 15.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(10, cell.value());
   EXPECT_TRUE(map.contains_entity(4));

   cell = map.add_entity(5, FPoint{5.0f, 25.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(20, cell.value());
   EXPECT_TRUE(map.contains_entity(5));

   cell = map.add_entity(6, FPoint{5.0f, 95.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(90, cell.value());
   EXPECT_TRUE(map.contains_entity(6));

   cell = map.add_entity(7, FPoint{55.0f, 55.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(55, cell.value());
   EXPECT_TRUE(map.contains_entity(7));

   cell = map.add_entity(8, FPoint{95.0f, 95.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(99, cell.value());
   EXPECT_TRUE(map.contains_entity(8));

   SpatialHashMap<300, 120, 50, 60> mapTwo;
   cell = mapTwo.add_entity(0, FPoint{170.0f, 20.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(3, cell.value());
   EXPECT_TRUE(mapTwo.contains_entity(0));

   cell = mapTwo.add_entity(1, FPoint{170.0f, 70.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(9, cell.value());
   EXPECT_TRUE(mapTwo.contains_entity(1));
}

TEST(SpatialHashMap, AddRectEntity) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<100, 100, 10, 10> map;

   auto cell = map.add_entity(0, FRect{0.0f, 0.0f, 10.0f, 10.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.add_entity(8, FRect{90.f, 90.f, 10.0f, 10.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(99, cell.value());
   EXPECT_TRUE(map.contains_entity(8));
}

TEST(SpatialHashMap, AddEntityBorderPosition) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<100, 100, 10, 10> map;

   auto cell = map.add_entity(0, FPoint{0.0f, 0.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.add_entity(1, FPoint{10.0f, 0.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(1, cell.value());
   EXPECT_TRUE(map.contains_entity(1));

   cell = map.add_entity(2, FPoint{10.0f, 10.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(11, cell.value());
   EXPECT_TRUE(map.contains_entity(2));
}

TEST(SpatialHashMap, MoveEntity) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<100, 100, 10, 10> map;

   map.add_entity(0, FPoint{0.0f, 0.0f});

   ASSERT_TRUE(map.contains_entity(0));

   auto cell = map.move_entity(0, FPoint{5.0f, 5.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.move_entity(0, FPoint{35.0f, 75.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(73, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.move_entity(0, FPoint{62.0f, 12.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(16, cell.value());
   EXPECT_TRUE(map.contains_entity(0));
}

TEST(SpatialHashMap, MoveRectEntity) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<100, 100, 10, 10> map;

   map.add_entity(0, FRect{0.0f, 0.0f, 10.0f, 10.0f});

   ASSERT_TRUE(map.contains_entity(0));

   auto cell = map.move_entity(0, FRect{1.0f, 1.0f, 10.0f, 10.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(0, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.move_entity(0, FRect{30.0f, 70.0f, 10.0f, 10.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(73, cell.value());
   EXPECT_TRUE(map.contains_entity(0));

   cell = map.move_entity(0, FRect{60.0f, 10.0f, 10.0f, 10.0f});
   ASSERT_TRUE(cell.has_value());
   EXPECT_EQ(16, cell.value());
   EXPECT_TRUE(map.contains_entity(0));
}

TEST(SpatialHashMap, RemoveEntity) 
{
   // Create a 100x100 space split in to ten cells x and ten cells y
   SpatialHashMap<100, 100, 10, 10> map;

   map.add_entity(0, FPoint{0.0f, 0.0f});
   map.add_entity(1, FPoint{30.0f, 60.0f});
   map.add_entity(2, FPoint{75.0f, 91.0f});

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
   SpatialHashMap<100, 100, 20, 20> map;

   // Center entity
   ASSERT_TRUE(map.add_entity(0, FPoint{55.0f, 50.0f}).has_value());

   // Expected neighboring entities
   //// Row above 
   ASSERT_TRUE(map.add_entity(1, FPoint{30.0f, 30.0f}).has_value());
   ASSERT_TRUE(map.add_entity(2, FPoint{55.0f, 30.0f}).has_value());
   ASSERT_TRUE(map.add_entity(3, FPoint{70.0f, 30.0f}).has_value());
   //// Same row
   ASSERT_TRUE(map.add_entity(4, FPoint{30.0f, 50.0f}).has_value());
   ASSERT_TRUE(map.add_entity(5, FPoint{45.0f, 50.0f}).has_value());
   ASSERT_TRUE(map.add_entity(6, FPoint{70.0f, 50.0f}).has_value());
   //// Row below 
   ASSERT_TRUE(map.add_entity(7, FPoint{30.0f, 70.0f}).has_value());
   ASSERT_TRUE(map.add_entity(8, FPoint{55.0f, 70.0f}).has_value());
   ASSERT_TRUE(map.add_entity(9, FPoint{70.0f, 70.0f}).has_value());

   // All non-neighboring cells are the borders of the grid, add these
   std::set<EntityId> non_neighboring_entities;
   auto current_id = 10;
   for (auto i=0; i<5; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, FPoint{10.0f*i, 10.0f}).has_value());
   }

   for (auto i=0; i<5; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, FPoint{10.0f*i, 90.0f}).has_value());
   }

   for (auto i=0; i<3; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, FPoint{10.0f, 10.0f+20.0f*i}).has_value());
   }

   for (auto i=0; i<3; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, FPoint{90.0f, 10.0f+20.0f*i}).has_value());
   }
   
   const auto neighbors = map.get_neighbors(0);
   EXPECT_FALSE(neighbors.empty());

   for (auto i=1; i<10; ++i) EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, i));
   for (const auto& non_neighbor : non_neighboring_entities) 
      EXPECT_EQ(neighbors.end(), std::ranges::find(neighbors, non_neighbor));
}

TEST(SpatialHashMap, GetNoNeighborsFromCenter) 
{
   SpatialHashMap<100, 100, 5, 5> map;

   // Center entity
   ASSERT_TRUE(map.add_entity(0, FPoint{55.0f, 50.0f}).has_value());

   // All non-neighboring cells are the borders of the grid, add these
   std::set<EntityId> non_neighboring_entities;
   auto current_id = 10;
   for (auto i=0; i<5; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, FPoint{10.0f*i, 10.0f}).has_value());
   }

   for (auto i=0; i<5; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, FPoint{10.0f*i, 90.0f}).has_value());
   }

   for (auto i=0; i<3; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, FPoint{10.0f, 10.0f+20.0f*i}).has_value());
   }

   for (auto i=0; i<3; ++i) 
   {
      non_neighboring_entities.insert(current_id);
      ASSERT_TRUE(map.add_entity(current_id++, FPoint{90.0f, 10.0f+20.0f*i}).has_value());
   }
   
   const auto neighbors = map.get_neighbors(0);
   EXPECT_TRUE(neighbors.empty());
}

TEST(SpatialHashMap, GetNoNeighborsInOneByOne) 
{
   SpatialHashMap<100, 100, 100, 100> map;

   ASSERT_TRUE(map.add_entity(0, FPoint{5.0f, 50.0f}).has_value());
   const auto neighbors = map.get_neighbors(0);
   EXPECT_TRUE(neighbors.empty());
}

TEST(SpatialHashMap, GetNeighborsInOneByTwo) 
{
   SpatialHashMap<100, 100, 100, 50> map;

   ASSERT_TRUE(map.add_entity(0, FPoint{25.0f, 25.0f}).has_value());
   ASSERT_TRUE(map.add_entity(1, FPoint{25.0f, 75.0f}).has_value());
   
   auto neighbors = map.get_neighbors(0);
   ASSERT_EQ(1, neighbors.size());
   EXPECT_EQ(1, *neighbors.begin());

   neighbors = map.get_neighbors(1);
   ASSERT_EQ(1, neighbors.size());
   EXPECT_EQ(0, *neighbors.begin());
}

TEST(SpatialHashMap, GetNeighborsInOneByThree) 
{
   SpatialHashMap<100, 90, 100, 30> map;

   ASSERT_TRUE(map.add_entity(0, FPoint{25.0f, 25.0f}).has_value());
   ASSERT_TRUE(map.add_entity(1, FPoint{25.0f, 50.0f}).has_value());
   ASSERT_TRUE(map.add_entity(2, FPoint{25.0f, 75.0f}).has_value());
   
   auto neighbors = map.get_neighbors(0);
   ASSERT_EQ(1, neighbors.size());
   EXPECT_EQ(1, *neighbors.begin());

   neighbors = map.get_neighbors(1);
   ASSERT_EQ(2, neighbors.size());
   EXPECT_EQ(0, *neighbors.begin());
   EXPECT_EQ(2, *++neighbors.begin());

   neighbors = map.get_neighbors(2);
   ASSERT_EQ(1, neighbors.size());
   EXPECT_EQ(1, *neighbors.begin());
}

TEST(SpatialHashMap, GetNeighborsInTwoByTwo) 
{
   SpatialHashMap<100, 100, 50, 50> map;

   ASSERT_TRUE(map.add_entity(0, FPoint{25.0f, 25.0f}).has_value());
   ASSERT_TRUE(map.add_entity(1, FPoint{25.0f, 75.0f}).has_value());
   ASSERT_TRUE(map.add_entity(2, FPoint{75.0f, 25.0f}).has_value());
   ASSERT_TRUE(map.add_entity(3, FPoint{75.0f, 75.0f}).has_value());
   
   auto neighbors = map.get_neighbors(0);
   ASSERT_EQ(3, neighbors.size());
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 1));
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 2));
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 3));

   neighbors = map.get_neighbors(1);
   ASSERT_EQ(3, neighbors.size());
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 0));
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 2));
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 3));

   neighbors = map.get_neighbors(2);
   ASSERT_EQ(3, neighbors.size());
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 0));
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 1));
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 3));

   neighbors = map.get_neighbors(3);
   ASSERT_EQ(3, neighbors.size());
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 0));
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 1));
   EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, 2));
}

TEST(SpatialHashMap, GetNeighborsInSevenByFive)
{ 
   // Not an uber interesting test, but this caused a runtime crash previously
   SpatialHashMap<700, 500, 100, 100> map;

   ASSERT_TRUE(map.add_entity(0, FPoint{ 650.0f, 350.0f }).has_value());
   ASSERT_TRUE(map.add_entity(1, FPoint{ 650.0f, 450.0f }).has_value());
   
   auto neighbors = map.get_neighbors(0);
   ASSERT_EQ(1, neighbors.size());
   EXPECT_EQ(1, neighbors[0]);

   neighbors = map.get_neighbors(1);
   ASSERT_EQ(1, neighbors.size());
   EXPECT_EQ(0, neighbors[0]);
}

TEST(SpatialHashMap, GetNeighborsInNonBorderingFrame)
{
   SpatialHashMap<700, 700, 100, 100> map;

   // Add entities where the entity value matches the cell # and is centered in the cell
   std::vector<EntityId> expected_values;
   for (auto i=0; i<49; ++i)
   {
      // Only the left most column and bottom most row will not be neighbors
      if (i % 7 != 0 && i < 42) expected_values.emplace_back(i);
      ASSERT_TRUE(map.add_entity(i, FPoint{ 50.0f + float(i % 7) * 100.0f, 
                                            50.0f + float(i / 7) * 100.0f }).has_value());
   }

   auto neighbors = map.get_neighbors({250.0f, 150.0f, 300.0f, 300.0f});
   EXPECT_EQ(neighbors.size(), expected_values.size());
   for (const auto& value : expected_values)
   {
      EXPECT_NE(neighbors.end(), std::ranges::find(neighbors, value));
   }
}