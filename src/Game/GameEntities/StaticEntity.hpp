#pragma once

#include "GameEntityDefs.hpp"

#include <assert.h>
#include <string>

namespace Game
{  

template <class T>
struct StaticEntity   
// class StaticEntity   
{
   const StaticEntityType m_type = StaticEntityType::invalid;
   const bool m_visible = true;
   const std::string m_label;
   const T m_data;

// public:

   StaticEntity() = delete;
   StaticEntity(const bool i_visible, std::string&& i_label, T&& i_data) noexcept;
   StaticEntity(const StaticEntity&) noexcept = default;
   StaticEntity(StaticEntity&&) noexcept = default;

   virtual ~StaticEntity() noexcept = default;

   StaticEntity& operator=(const StaticEntity&) noexcept = default;
   StaticEntity& operator=(StaticEntity&&) noexcept = default;

   // StaticEntityType get_type() const { return m_type; }
   // bool is_visible() const { return m_visible; }
   // const std::string& get_label() const { return m_label; }
   // const T& get_data() const { return m_data; }

};

template <class T>
StaticEntity<T>::StaticEntity(const bool i_visible, 
                              std::string&& i_label, 
                              T&& i_data) noexcept
{ 
   assert(false && "Do not use the unspecialized constructor of this class!");
}

} // namespace StaticEntity
