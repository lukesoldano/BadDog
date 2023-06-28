#include <gtest/gtest.h>

#include "JsonDefs.hpp"
#include "JsonFileReader.hpp"

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
   auto file_info = json.value().at(Keys::FILE_INFO_OBJECT).get<FileInfo>();
   EXPECT_EQ(file_info.m_type, "Level");
   EXPECT_EQ(file_info.m_authors.size(), 1);
   EXPECT_EQ(file_info.m_authors[0], "Luke Soldano");
   EXPECT_EQ(file_info.m_creation_date, "2023-04-16");
}