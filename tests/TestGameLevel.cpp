#include <gtest/gtest.h>

#include "GameLevel.hpp"
#include "JsonDefs.hpp"
#include "JsonFileReader.hpp"

using namespace Game;
using namespace JSON;

TEST(GameLevel, ParseJsonLevelFile)
{
   std::filesystem::path path(JSON_LEVEL_ASSETS_DIRECTORY);
   path.append("TestLevel.json");
   auto json = FileReader::read_json_file(path);
   ASSERT_TRUE(json.has_value());
   auto level = json.value().at(Keys::LEVEL_INFO_OBJECT).get<Level>();

   EXPECT_EQ(level.m_name, "Test Level");
   EXPECT_EQ(level.m_width, 2000);
   EXPECT_EQ(level.m_height, 2000);
   EXPECT_EQ(level.m_border_width, 10);

   ASSERT_EQ(level.m_static_entities.size(), 2);

   EXPECT_EQ(level.m_static_entities[0].m_label, "Test Rect 1");
   ASSERT_TRUE(std::holds_alternative<RectEntity>(level.m_static_entities[0].m_data));
   EXPECT_TRUE(std::get<RectEntity>(level.m_static_entities[0].m_data).m_visible);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[0].m_data).x, 100);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[0].m_data).y, 100);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[0].m_data).w, 20);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[0].m_data).h, 20);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[0].m_data).m_rgba_color, RgbaColor(Color::red));

   EXPECT_EQ(level.m_static_entities[1].m_label, "Test Rect 2");
   ASSERT_TRUE(std::holds_alternative<RectEntity>(level.m_static_entities[1].m_data));
   EXPECT_TRUE(std::get<RectEntity>(level.m_static_entities[1].m_data).m_visible);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[1].m_data).x, 200);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[1].m_data).y, 200);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[1].m_data).w, 40);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[1].m_data).h, 60);
   EXPECT_EQ(std::get<RectEntity>(level.m_static_entities[1].m_data).m_rgba_color, RgbaColor(Color::blue));
}