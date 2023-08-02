#include "EntityIdManager.hpp"

#include "ProjectMacros.hpp"

using namespace Entity;

EntityId IdManager::allocate_id(EntityType i_type)
{
   if (EntityType::player_one == i_type || EntityType::player_two == i_type)
   {
      m_type_id_map[i_type].insert(DEFAULT_ENTITY_TYPE_ID);
      return EntityType::player_one == i_type ? PLAYER_ONE_ENTITY_ID : PLAYER_TWO_ENTITY_ID;
   }

   if (false == m_type_id_map.contains(i_type))
   {
      if (EntityType::player_one == i_type || EntityType::player_two == i_type)
      {
         m_type_id_map[i_type].insert(DEFAULT_ENTITY_TYPE_ID);
         return EntityType::player_one == i_type ? PLAYER_ONE_ENTITY_ID : PLAYER_TWO_ENTITY_ID;
      }

      auto result_pair = m_type_id_map[i_type].insert(m_type_id_generator.get_random_number());
      return get_entity_id(i_type, *result_pair.first);
   }

   constexpr auto MAX_RANDOM_NUMBER_ATTEMPTS = 10;
   for (auto attempts = 0; attempts < MAX_RANDOM_NUMBER_ATTEMPTS; ++attempts)
   {
      auto type_id = m_type_id_generator.get_random_number();
      if (false == m_type_id_map[i_type].contains(type_id))
      {
         m_type_id_map[i_type].insert(type_id);
         return get_entity_id(i_type, type_id);
      }
   }

   ASSERT("Failed to randomly generate a unique value to allocate entity id");

   return INVALID_ENTITY_ID;
}

EntityId IdManager::deallocate_id(EntityId i_id)
{
   const auto map_it = m_type_id_map.find(get_entity_type(i_id));
   if (map_it != m_type_id_map.end())
   {
      const auto set_it = map_it->second.find(get_entity_type_id(i_id));
      if (set_it != map_it->second.end())
      {
         map_it->second.erase(set_it);
         if (map_it->second.empty()) m_type_id_map.erase(map_it);

         return i_id;
      }
   }

   return INVALID_ENTITY_ID;
}