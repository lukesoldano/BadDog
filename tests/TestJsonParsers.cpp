#include <gtest/gtest.h>

#include "JsonFileReader.hpp"
#include "JsonLevelParser.hpp"

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
}