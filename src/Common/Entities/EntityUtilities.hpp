#pragma once

#include "EntityTypes.hpp"

#include <concepts>
#include <type_traits>

namespace Entity
{

constexpr uint64_t ENTITY_TYPE_SHIFT = 32;
constexpr uint64_t ENTITY_TYPE_ID_MASK = 0x00000000FFFFFFFF;
constexpr uint64_t ENTITY_TYPE_MASK = 0xFFFFFFFF00000000;

template <typename T>
concept IsEntity = std::is_same_v<EntityId, std::decay_t<T>>;

template <IsEntity T>
constexpr inline EntityTypeId get_entity_type_id(T i_id) 
{
   return static_cast<EntityTypeId>(i_id & ENTITY_TYPE_ID_MASK);
}

template <IsEntity T>
constexpr inline EntityType get_entity_type(T i_id)
{
   return static_cast<EntityType>(i_id >> ENTITY_TYPE_SHIFT);
}

constexpr inline EntityId get_entity_id(EntityType i_type, EntityTypeId i_type_id)
{
   return (static_cast<EntityId>(i_type) << ENTITY_TYPE_SHIFT) | i_type_id;
}

template <IsEntity T>
constexpr inline bool is_entity_type(T i_id, EntityType i_type) 
{
   return get_entity_type(i_id) == i_type;
}

constexpr inline bool masks_for_entity_type(EntityType i_type_one, EntityType i_type_two) 
{
   return static_cast<std::underlying_type_t<EntityType>>(i_type_one) & 
          static_cast<std::underlying_type_t<EntityType>>(i_type_two);
}

template <IsEntity T>
constexpr inline bool masks_for_entity_type(T i_id, EntityType i_type) 
{
   return masks_for_entity_type(static_cast<EntityType>((i_id & ENTITY_TYPE_MASK) >> ENTITY_TYPE_SHIFT), 
                                i_type);
}

} // namespace Entity