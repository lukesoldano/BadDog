#pragma once

#include "JsonDefs.hpp"
#include "ProjectDefs.hpp"
#include "StationaryDynamicEntityTypes.hpp"

#include <string>
#include <variant>

namespace Game
{  

// Class is JSON deserializable
struct StaticEntity;
void from_json(const nlohmann::json& i_json, StaticEntity& o_static_entity);

struct StationaryDynamicEntity
{
   std::string m_label;
   std::variant<DogBone> m_data;

   FRect get_hitbox() const
   {
      static FRect DEFAULT_HITBOX{-100.0f, -100.0f, 0.0f, 0.0f};
      if (std::holds_alternative<DogBone>(m_data)) return std::get<DogBone>(m_data).get_hitbox();
      else ASSERT("StationaryDynamicEntity does not contain any data!");
      return DEFAULT_HITBOX;
   }
};

inline void from_json(const nlohmann::json& i_json, StationaryDynamicEntity& o_stationary_dynamic_entity)
{
   o_stationary_dynamic_entity.m_label = i_json.at("m_label").get<std::string>();
   if (i_json.contains("m_dog_bone")) o_stationary_dynamic_entity.m_data = i_json.at("m_dog_bone").get<DogBone>();
   else ASSERT("StationaryDynamicEntity does not contain any data!");
}

} // namespace Game