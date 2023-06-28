#pragma once

#include "GameEntityDefs.hpp"
#include "JsonDefs.hpp"
#include "ProjectDefs.hpp"

#include <string>
#include <variant>

namespace Game
{  

// Class is JSON deserializable
struct StaticEntity;
void from_json(const nlohmann::json& i_json, StaticEntity& o_static_entity);

struct StaticEntity   
{
   std::string m_label;
   std::variant<FRectEntity> m_data;
};

inline void from_json(const nlohmann::json& i_json, StaticEntity& o_static_entity)
{
   o_static_entity.m_label = i_json.at("m_label").get<std::string>();
   if (i_json.contains("m_frect")) o_static_entity.m_data = i_json.at("m_frect").get<FRectEntity>();
   else ASSERT("Static Entity does not contain any data!");
}

} // namespace Game
