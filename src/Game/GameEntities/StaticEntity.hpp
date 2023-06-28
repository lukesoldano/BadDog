#pragma once

#include "GameEntityDefs.hpp"

#include <string>
#include <variant>

namespace Game
{  

struct StaticEntity   
{
   const bool m_visible = true;
   const std::string m_label = "default";
   const std::variant<RectEntity> m_data;

   StaticEntity() = delete;
   StaticEntity(const bool i_visible, std::string&& i_label, auto&& i_data) noexcept;
   StaticEntity(const StaticEntity&) noexcept = default;
   StaticEntity(StaticEntity&&) noexcept = default;

   virtual ~StaticEntity() noexcept = default;

   StaticEntity& operator=(const StaticEntity&) noexcept = default;
   StaticEntity& operator=(StaticEntity&&) noexcept = default;

};

StaticEntity::StaticEntity(const bool i_visible, std::string&& i_label, auto&& i_data) noexcept :
   m_visible(i_visible),
   m_label(std::move(i_label)),
   m_data(std::forward<decltype(i_data)>(i_data)) {}

} // namespace Game
