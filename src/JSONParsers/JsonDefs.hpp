#pragma once

#include <nlohmann/json.hpp>

#include <optional>
#include <string>
#include <vector>

namespace JSON
{

struct FileInfo
{
   std::string m_name;
   std::string m_type;
   std::vector<std::string> m_authors;
   std::string m_creation_date;
   std::string m_last_updated_date;

   static std::optional<FileInfo> from_json(const std::string& i_file_name,
                                            const nlohmann::json& i_json) noexcept;
};

namespace Keys
{

// Header keys (Common to all file types)
constexpr auto FILE_INFO_OBJECT = "fileInfo";
constexpr auto FILE_TYPE = "type";
constexpr auto FILE_AUTHORS_ARRAY = "authors";
constexpr auto FILE_CREATION_DATE = "creationDate";
constexpr auto FILE_LAST_UPDATED_DATE = "lastUpdatedDate";

// Level  keys
//// Level info keys (Common to all level files)
constexpr auto LEVEL_INFO_OBJECT = "levelInfo";
constexpr auto LEVEL_NAME = "name";
constexpr auto LEVEL_WIDTH = "width";
constexpr auto LEVEL_HEIGHT = "height";
constexpr auto LEVEL_BORDER_WIDTH = "borderWidth";
constexpr auto LEVEL_STATIC_ENTITIES_ARRAY = "staticEntities";
constexpr auto LEVEL_ACTIVE_ENTITIES_ARRAY = "activeEntities";
////

// Static entity keys (Common to all static entities)
constexpr auto STATIC_ENTITY_TYPE = "type";
constexpr auto STATIC_ENTITY_VISIBILITY = "visible";
constexpr auto STATIC_ENTITY_INSTANCES = "instances";

//// Static entity keys (Common to all instances)
constexpr auto STATIC_ENTITY_LABEL = "label";
constexpr auto STATIC_ENTITY_X = "x";
constexpr auto STATIC_ENTITY_Y = "y";

//// Static rect entity keys (Common to all rect)
constexpr auto STATIC_ENTITY_RECT_WIDTH = "width";
constexpr auto STATIC_ENTITY_RECT_HEIGHT = "height";
constexpr auto STATIC_ENTITY_RECT_COLOR = "color";

} // namespace Keys

} // namespace JSON