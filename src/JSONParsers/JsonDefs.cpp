#include "JsonDefs.hpp"

#include "JsonUtilities.hpp"

using namespace JSON;

std::optional<FileInfo> FileInfo::from_json(const std::string& i_file_name,
                                            const nlohmann::json& i_json) noexcept
{
   CHECK_JSON_OBJECT_RETURN_NULLOPT(i_json);
   CHECK_CONDITION_RETURN_NULLOPT(i_json.contains(Keys::FILE_INFO_OBJECT));
   const auto file_info_json = i_json[Keys::FILE_INFO_OBJECT];

   std::string type;
   std::vector<std::string> authors;
   std::string creation_date;
   std::string last_updated_date;

   // Silent failures possible
   Utilities::get_json_value(file_info_json, Keys::FILE_TYPE, type);
   Utilities::get_json_value(file_info_json, Keys::FILE_AUTHORS_ARRAY, authors);
   Utilities::get_json_value(file_info_json, Keys::FILE_CREATION_DATE, creation_date);
   Utilities::get_json_value(file_info_json, Keys::FILE_LAST_UPDATED_DATE, last_updated_date);
   
   return FileInfo{ i_file_name,
                    std::move(type),
                    std::move(authors),
                    std::move(creation_date),
                    std::move(last_updated_date) };
}