#include <gtest/gtest.h>

#include "EntityIdManager.hpp"
#include "GameLevelLoader.hpp"

using namespace Game;

TEST(GameLevelLoader, LoadFromJson) 
{
   std::filesystem::path test_level_json_path{JSON_LEVEL_ASSETS_DIRECTORY};
   test_level_json_path /= "TestLevel2.json";

   auto level_opt = LevelLoader().load_from_json(test_level_json_path);
   ASSERT_TRUE(level_opt.has_value());

   const auto& level = level_opt.value();
   EXPECT_EQ(level.m_name, "Test Level");

   const auto& level_dimmensions = level.m_dimmensions;

   EXPECT_EQ(level_dimmensions.m_width, 2000);
   EXPECT_EQ(level_dimmensions.m_height, 2000);
   EXPECT_EQ(level_dimmensions.m_border_width, 10);

   const auto& shm = level.m_spatial_hash_map;

   EXPECT_EQ(shm.get_width(), 2000);
   EXPECT_EQ(shm.get_height(), 2000);
   EXPECT_EQ(shm.get_cell_width(), 100);
   EXPECT_EQ(shm.get_cell_height(), 100);

   const auto& entity_id_manager = Entity::IdManager::instance();

   ASSERT_TRUE(entity_id_manager.is_id_allocated(Entity::PLAYER_ONE_ENTITY_ID));
   ASSERT_TRUE(entity_id_manager.is_id_allocated(Entity::PLAYER_TWO_ENTITY_ID));

   const auto& named_entities = level.m_named_entities;

   ASSERT_TRUE(named_entities.contains(Entity::PLAYER_ONE_ENTITY_ID));
   EXPECT_EQ(named_entities.at(Entity::PLAYER_ONE_ENTITY_ID), "Player 1");
   ASSERT_TRUE(named_entities.contains(Entity::PLAYER_TWO_ENTITY_ID));
   EXPECT_EQ(named_entities.at(Entity::PLAYER_TWO_ENTITY_ID), "Player 2");

   const auto& positionable_entities = level.m_positionable_entities;

   ASSERT_TRUE(positionable_entities.contains(Entity::PLAYER_ONE_ENTITY_ID));
   FPosition player_one_position = positionable_entities.at(Entity::PLAYER_ONE_ENTITY_ID);
   EXPECT_EQ(player_one_position, FPosition(1000.0f, 1000.0f));
   ASSERT_TRUE(positionable_entities.contains(Entity::PLAYER_TWO_ENTITY_ID));
   FPosition player_two_position = positionable_entities.at(Entity::PLAYER_TWO_ENTITY_ID);
   EXPECT_EQ(player_two_position, FPosition(1050.0f, 1000.0f));
}