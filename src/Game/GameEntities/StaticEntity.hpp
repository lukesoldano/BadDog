#pragma once

#include "GameEntityDefs.hpp"
#include "JsonDefs.hpp"
#include "ProjectDefs.hpp"

#include <string>
#include <variant>

namespace Game
{  

struct StaticEntity   
{
   std::string m_label;
   std::variant<RectEntity> m_data;
};

void from_json(const nlohmann::json& i_json, StaticEntity& o_static_entity)
{
   o_static_entity.m_label = i_json.at("m_label").get<std::string>();
   LOG_MESSAGE(i_json.dump(4));
   if (i_json.contains("m_rect")) o_static_entity.m_data = i_json.at("m_rect").get<RectEntity>();
   else ASSERT("Static Entity does not contain any data!");
}

} // namespace Game
