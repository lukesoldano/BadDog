#include <gtest/gtest.h>

#include "GameState.hpp"
#include "TestLevel.hpp"

using namespace Game;
using namespace JSON;

TEST(GameState, LoadLevel)
{
   auto& game_state = State::instance();
   ASSERT_TRUE(game_state.load_level(TestLevel()));

   // Verify level was loaded, check something easy like the name
   auto& level_opt = game_state.get_level();
   ASSERT_TRUE(level_opt);
   auto& level = level_opt.value();
   EXPECT_EQ(level.m_name, "Test Level");

   // Verify spatial hash map was created
   auto& shm = game_state.m_spatial_hash_map;
   EXPECT_EQ(shm.get_width(), level.m_width);
   EXPECT_EQ(shm.get_height(), level.m_height);
   EXPECT_EQ(shm.get_cell_width(), level.m_shm_cell_width);
   EXPECT_EQ(shm.get_cell_height(), level.m_shm_cell_height);
}