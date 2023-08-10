#pragma once

#include "ExtendedOptional.hpp"
#include "JsonTypes.hpp"

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

namespace JSON
{

struct FileInfo
{
   std::string m_type;
   std::vector<std::string> m_authors;
   std::string m_creation_date;
   std::string m_last_updated_date;

   NLOHMANN_DEFINE_TYPE_INTRUSIVE(FileInfo, 
                                  m_type, 
                                  m_authors, 
                                  m_creation_date, 
                                  m_last_updated_date);
};

namespace FileReader
{

   bool is_json_file(const std::filesystem::path& i_file_path) noexcept;
   extended_opt<std::pair<FileInfo, json>> read_json_file(std::filesystem::path i_json_file) noexcept;

} // namespace FileReader

} // namespace JSON
