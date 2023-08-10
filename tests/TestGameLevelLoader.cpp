#include <gtest/gtest.h>

#include "GameLevelLoader.hpp"

using namespace Game;

TEST(GameLevelLoader, LoadFromJson) 
{
   std::filesystem::path test_level_json_path{JSON_LEVEL_ASSETS_DIRECTORY};
   test_level_json_path /= "TestLevel2.json";

   auto level_opt = LevelLoader::load_from_json(test_level_json_path);
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

}