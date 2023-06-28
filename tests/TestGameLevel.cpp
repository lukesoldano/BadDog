#include <gtest/gtest.h>

#include "GameLevel.hpp"
#include "SpatialHashMap.hpp"

using namespace Game;
using namespace JSON;

TEST(GameLevel, ParseJsonLevelFile)
{
   std::filesystem::path path(JSON_LEVEL_ASSETS_DIRECTORY);
   path.append("TestLevel.json");
   Level level(std::move(path));

   EXPECT_EQ(level.m_name, "Test Level");
   EXPECT_EQ(level.m_width, 2000);
   EXPECT_EQ(level.m_height, 2000);
   EXPECT_EQ(level.m_shm_cell_width, 100);
   EXPECT_EQ(level.m_shm_cell_height, 100);
   EXPECT_EQ(level.m_border_width, 10);
   EXPECT_EQ(level.m_player_start_x, 1000.0f);
   EXPECT_EQ(level.m_player_start_y, 1000.0f);

   // Just verify first two entities, will add more as I mess around, but this is enough to verify 
   // the concept
   ASSERT_TRUE(level.m_static_entities.size() >= 2);

   EXPECT_EQ(level.m_static_entities[0].m_label, "Test Rect 1");
   ASSERT_TRUE(std::holds_alternative<FRectBarrier>(level.m_static_entities[0].m_data));
   EXPECT_TRUE(std::get<FRectBarrier>(level.m_static_entities[0].m_data).m_visible);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[0].m_data).x, 100.0f);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[0].m_data).y, 100.0f);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[0].m_data).w, 20.0f);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[0].m_data).h, 20.0f);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[0].m_data).m_rgba_color, RgbaColor(Color::red));

   EXPECT_EQ(level.m_static_entities[1].m_label, "Test Rect 2");
   ASSERT_TRUE(std::holds_alternative<FRectBarrier>(level.m_static_entities[1].m_data));
   EXPECT_TRUE(std::get<FRectBarrier>(level.m_static_entities[1].m_data).m_visible);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[1].m_data).x, 200.0f);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[1].m_data).y, 200.0f);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[1].m_data).w, 40.0f);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[1].m_data).h, 60.0f);
   EXPECT_EQ(std::get<FRectBarrier>(level.m_static_entities[1].m_data).m_rgba_color, RgbaColor(Color::blue));
}