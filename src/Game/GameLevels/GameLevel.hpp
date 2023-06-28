#pragma once

#include "JsonDefs.hpp"
#include "StaticEntity.hpp"

#include <string>
#include <vector>

namespace Game 
{

struct Level
{
   std::string m_name;
   size_t m_width;
   size_t m_height;
   size_t m_border_width;

   std::vector<StaticEntity> m_static_entities;
};

void from_json(const nlohmann::json& i_json, Level& o_level)
{
   o_level.m_name = i_json.at("m_name").get<std::string>();
   o_level.m_width = i_json.at("m_width").get<size_t>();
   o_level.m_height = i_json.at("m_height").get<size_t>();
   o_level.m_border_width = i_json.at("m_border_width").get<size_t>();
   o_level.m_static_entities = i_json.at("m_static_entities").get<std::vector<StaticEntity>>();
}

} // namespace Game