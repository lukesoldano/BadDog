#include <gtest/gtest.h>

#include "GameLevel.hpp"

using namespace Game;

TEST(GameLevel, Clear) 
{
   Level level;

   level.m_name = "Test Level";

   level.m_dimmensions.m_width = 2000;
   level.m_dimmensions.m_height = 2000;
   level.m_dimmensions.m_border_width = 10;

   level.m_spatial_hash_map = SpatialHashMap{2000, 2000, 100, 100};

   const EntityId id = 0;
   level.m_spatial_hash_map.add_entity(id, {100.0f, 100.0f});
   level.m_named_entities[id] = "Player 1";
   level.m_positionable_entities[id] = {100.0f, 100.0f};

   level.clear();

   EXPECT_TRUE(level.m_name.empty());

   EXPECT_EQ(level.m_dimmensions.m_width, 0);
   EXPECT_EQ(level.m_dimmensions.m_height, 0);
   EXPECT_EQ(level.m_dimmensions.m_border_width, 0);

   EXPECT_FALSE(level.m_spatial_hash_map.contains_entity(id));

   EXPECT_TRUE(level.m_named_entities.empty());

   EXPECT_TRUE(level.m_positionable_entities.empty());
}

TEST(GameLevel, ClearEntity) 
{
   Level level;

   level.m_name = "Test Level";

   level.m_dimmensions.m_width = 2000;
   level.m_dimmensions.m_height = 2000;
   level.m_dimmensions.m_border_width = 10;

   level.m_spatial_hash_map = SpatialHashMap{2000, 2000, 100, 100};

   const EntityId id_one = 0;
   level.m_spatial_hash_map.add_entity(id_one, {100.0f, 100.0f});
   level.m_named_entities[id_one] = "Player 1";
   level.m_positionable_entities[id_one] = {100.0f, 100.0f};

   const EntityId id_two = 1;
   level.m_spatial_hash_map.add_entity(id_two, {100.0f, 100.0f});
   level.m_named_entities[id_two] = "Player 2";
   level.m_positionable_entities[id_two] = {100.0f, 100.0f};

   level.clear_entity(id_one);

   EXPECT_EQ("Test Level", level.m_name);

   EXPECT_EQ(level.m_dimmensions.m_width, 2000);
   EXPECT_EQ(level.m_dimmensions.m_height, 2000);
   EXPECT_EQ(level.m_dimmensions.m_border_width, 10);

   EXPECT_FALSE(level.m_spatial_hash_map.contains_entity(id_one));
   EXPECT_TRUE(level.m_spatial_hash_map.contains_entity(id_two));

   EXPECT_FALSE(level.m_named_entities.empty());
   EXPECT_FALSE(level.m_named_entities.contains(id_one));
   EXPECT_TRUE(level.m_named_entities.contains(id_two));

   EXPECT_FALSE(level.m_positionable_entities.empty());
   EXPECT_FALSE(level.m_positionable_entities.contains(id_one));
   EXPECT_TRUE(level.m_positionable_entities.contains(id_two));
}