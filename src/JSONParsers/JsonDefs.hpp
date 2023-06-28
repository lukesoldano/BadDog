#pragma once

#include "Logger.hpp"
#include "ProjectDefs.hpp"

#include <nlohmann/json.hpp>

#include <assert.h>
#include <optional>
#include <string>
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

namespace Keys
{

constexpr auto FILE_INFO_OBJECT = "file_info";
constexpr auto LEVEL_INFO_OBJECT = "level_info";

} // namespace Keys

} // namespace JSON