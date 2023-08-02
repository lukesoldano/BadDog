#pragma once

#include "EntityTypes.hpp"
#include "EntityUtilities.hpp"
#include "RandomNumberGenerator.hpp"

#include <set>
#include <unordered_map>

namespace Entity
{

constexpr EntityTypeId DEFAULT_ENTITY_TYPE_ID = 0;
constexpr EntityId PLAYER_ONE_ENTITY_ID = get_entity_id(EntityType::player_one, 
                                                        DEFAULT_ENTITY_TYPE_ID);
constexpr EntityId PLAYER_TWO_ENTITY_ID = get_entity_id(EntityType::player_two, 
                                                        DEFAULT_ENTITY_TYPE_ID);

class IdManager
{
   RandomNumberGenerator<EntityTypeId> m_type_id_generator;

   std::unordered_map<EntityType, std::set<EntityTypeId>> m_type_id_map;

public:

   IdManager(const IdManager&) = delete;
   IdManager(IdManager&&) = delete;

   IdManager& operator=(const IdManager&) = delete;
   IdManager& operator=(IdManager&&) = delete;

   inline static IdManager& instance()
   {
      static IdManager manager;
      return manager;
   }

   EntityId allocate_id(EntityType i_type);
   EntityId deallocate_id(EntityId i_id);

private:

   IdManager() = default;
   virtual ~IdManager() = default;

};

} // namespace Entity