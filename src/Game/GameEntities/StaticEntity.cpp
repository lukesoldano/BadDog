#include "StaticEntity.hpp"

using namespace Game;

template <>
StaticEntity<RectEntity>::StaticEntity(const bool i_visible, 
                                       std::string&& i_label, 
                                       RectEntity&& i_data) noexcept : 
   m_type(StaticEntityType::rect),
   m_visible(i_visible),
   m_label(std::move(i_label)),
   m_data(std::move(i_data)) {}