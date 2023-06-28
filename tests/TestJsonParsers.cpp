#include <gtest/gtest.h>

#include "JsonDefs.hpp"
#include "JsonFileReader.hpp"
#include "JsonLevelParser.hpp"

using namespace Game;
using namespace JSON;

TEST(JsonReader, ReadJsonFile) 
{
   std::filesystem::path path(JSON_LEVEL_ASSETS_DIRECTORY);
   path.append("TestLevel.json");
   auto json = FileReader::read_json_file(path);
   ASSERT_TRUE(json.has_value());
}

TEST(JsonReader, ReadJsonFileBadPath)
{
   std::filesystem::path path(JSON_LEVEL_ASSETS_DIRECTORY);
   path.append("TestLevelBadPath.json");
   auto json = FileReader::read_json_file(path);
   ASSERT_FALSE(json.has_value());
}

TEST(JsonReader, ParseJsonFileInfo)
{
   std::filesystem::path path(JSON_LEVEL_ASSETS_DIRECTORY);
   path.append("TestLevel.json");
   auto json = FileReader::read_json_file(path);
   ASSERT_TRUE(json.has_value());
   auto file_info = FileInfo::from_json("TestLevel.json", json.value());
   ASSERT_TRUE(file_info.has_value());
   EXPECT_EQ(file_info.value().m_name, "TestLevel.json");
   EXPECT_EQ(file_info.value().m_type, "Level");
   EXPECT_EQ(file_info.value().m_authors.size(), 1);
   EXPECT_EQ(file_info.value().m_authors[0], "Luke Soldano");
   EXPECT_EQ(file_info.value().m_creation_date, "2023-04-16");
}

TEST(JsonLevelParser, ParseLevelFile)
{
   std::filesystem::path path(JSON_LEVEL_ASSETS_DIRECTORY);
   path.append("TestLevel.json");
   auto json = FileReader::read_json_file(path);
   ASSERT_TRUE(json.has_value());
   auto level = LevelParser::get_game_level_from_json(json.value());
   ASSERT_TRUE(level.has_value());

   const auto& level_value = level.value();
   EXPECT_EQ(level_value.m_name, "Test Level");
   EXPECT_EQ(level_value.m_width, 2000);
   EXPECT_EQ(level_value.m_height, 2000);
   EXPECT_EQ(level_value.m_border_width, 10);

   ASSERT_EQ(level_value.m_static_entities.size(), 2);

   EXPECT_TRUE(level_value.m_static_entities[0].m_visible);
   EXPECT_EQ(level_value.m_static_entities[0].m_label, "Test Rect 1");
   ASSERT_TRUE(std::holds_alternative<RectEntity>(level_value.m_static_entities[0].m_data));
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[0].m_data).x, 100);
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[0].m_data).y, 100);
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[0].m_data).w, 20);
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[0].m_data).h, 20);
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[0].m_data).m_color, Color::red);

   EXPECT_TRUE(level_value.m_static_entities[1].m_visible);
   EXPECT_EQ(level_value.m_static_entities[1].m_label, "Test Rect 2");
   ASSERT_TRUE(std::holds_alternative<RectEntity>(level_value.m_static_entities[1].m_data));
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[1].m_data).x, 200);
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[1].m_data).y, 200);
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[1].m_data).w, 40);
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[1].m_data).h, 60);
   EXPECT_EQ(std::get<RectEntity>(level_value.m_static_entities[1].m_data).m_color, Color::blue);
}