#include <gtest/gtest.h>

#include "JsonFileReader.hpp"

using namespace JSON;

TEST(JsonFileReader, IsJsonFile)
{
   const std::filesystem::path test_level_dir_path{JSON_LEVEL_ASSETS_DIRECTORY};
   const auto test_level_file_path = test_level_dir_path / "TestLevel2.json";
   const auto non_json_file_path = test_level_dir_path / "TestLevel2.png";
   const auto bad_file_path = test_level_dir_path / "aasdasdasd.json";

   EXPECT_FALSE(FileReader::is_json_file(test_level_dir_path));
   EXPECT_TRUE(FileReader::is_json_file(test_level_file_path));
   EXPECT_FALSE(FileReader::is_json_file(non_json_file_path));
} 

TEST(JsonFileReader, ReadJsonFile)
{
   const std::filesystem::path test_level_dir_path{JSON_LEVEL_ASSETS_DIRECTORY};
   const auto test_level_file_path = test_level_dir_path / "TestLevel2.json";

   const auto json_file_pair = FileReader::read_json_file(test_level_file_path);
   ASSERT_TRUE(json_file_pair.has_value());

   const auto& file_info = json_file_pair.value().first;
   const auto& json_object = json_file_pair.value().second;

   EXPECT_NE(std::string::npos, file_info.m_file_path.find("TestLevel2.json"));
   EXPECT_EQ(file_info.m_type, "Level");
   EXPECT_EQ(file_info.m_authors.size(), 1);
   EXPECT_EQ("2023-07-19", file_info.m_creation_date);
   EXPECT_FALSE(file_info.m_last_updated_date.empty());

   EXPECT_TRUE(json_object.is_object());

   json file_info_json;
   EXPECT_TRUE(get_json_value(json_object, "file_info", file_info_json));
   EXPECT_TRUE(file_info_json.is_object());

   const auto non_json_file_path = test_level_dir_path / "TestLevel2.png";
   const auto non_json_file_pair = FileReader::read_json_file(non_json_file_path);
   EXPECT_FALSE(non_json_file_pair.has_value());

   const auto bad_file_path = test_level_dir_path / "aasdasdasd.json";
   const auto bad_file_pair = FileReader::read_json_file(bad_file_path);
   EXPECT_FALSE(bad_file_pair.has_value());
}