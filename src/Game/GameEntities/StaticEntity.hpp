#pragma once

#include "JsonDefs.hpp"
#include "ProjectDefs.hpp"
#include "StaticEntityTypes.hpp"

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
   std::variant<FRectBarrier> m_data;

   const FRect& get_hitbox() const
   {
      static FRect DEFAULT_HITBOX{-100.0f, -100.0f, 0.0f, 0.0f};
      if (std::holds_alternative<FRectBarrier>(m_data)) return std::get<FRectBarrier>(m_data);
      else ASSERT("StaticEntity does not contain any data!");
      return DEFAULT_HITBOX;
   }
};

inline void from_json(const nlohmann::json& i_json, StaticEntity& o_static_entity)
{
   o_static_entity.m_label = i_json.at("m_label").get<std::string>();
   if (i_json.contains("m_frect_barrier")) o_static_entity.m_data = i_json.at("m_frect_barrier").get<FRectBarrier>();
   else ASSERT("StaticEntity does not contain any data!");
}

} // namespace Game
