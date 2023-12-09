#include "EntityIdManager.hpp"

#include "Logger.hpp"
#include "ProjectMacros.hpp"

using namespace Entity;

bool IdManager::is_id_allocated(EntityId i_id) const
{
   const auto type = get_entity_type(i_id);
   const auto type_id = get_entity_type_id(i_id);

   const auto map_it = m_type_id_map.find(type);
   if (map_it == m_type_id_map.end()) return false;

   return map_it->second.find(type_id) != map_it->second.end();
}

EntityId IdManager::allocate_id(EntityType i_type)
{
   if (EntityType::player_one == i_type || EntityType::player_two == i_type)
   {
      m_type_id_map[i_type].insert(DEFAULT_ENTITY_TYPE_ID);
      LOG_VERBOSE("Allocated entity id for player: " << i_type);
      return EntityType::player_one == i_type ? PLAYER_ONE_ENTITY_ID : PLAYER_TWO_ENTITY_ID;
   }

   if (false == m_type_id_map.contains(i_type))
   {
      const auto result_pair = m_type_id_map[i_type].insert(m_type_id_generator.get_random_number());

      const auto entity_id = get_entity_id(i_type, *result_pair.first);
      LOG_VERBOSE("Allocated entity id: " << std::hex << entity_id << " for type: " << i_type);
      
      return entity_id;
   }

   constexpr auto MAX_RANDOM_NUMBER_ATTEMPTS = 10;
   for (auto attempts = 0; attempts < MAX_RANDOM_NUMBER_ATTEMPTS; ++attempts)
   {
      const auto type_id = m_type_id_generator.get_random_number();
      if (false == m_type_id_map[i_type].contains(type_id))
      {
         m_type_id_map[i_type].insert(type_id);

         const auto entity_id = get_entity_id(i_type, type_id);
         LOG_VERBOSE("Allocated entity id: " << std::hex << entity_id << " for type: " << i_type);
         
         return get_entity_id(i_type, type_id);
      }
   }

   ASSERT("Failed to randomly generate a unique value to allocate entity id");

   return INVALID_ENTITY_ID;
}

EntityId IdManager::deallocate_id(EntityId i_id)
{
   if (INVALID_ENTITY_ID == i_id) return INVALID_ENTITY_ID;
   
   const auto map_it = m_type_id_map.find(get_entity_type(i_id));
   if (map_it != m_type_id_map.end())
   {
      const auto set_it = map_it->second.find(get_entity_type_id(i_id));
      if (set_it != map_it->second.end())
      {
         map_it->second.erase(set_it);
         LOG_VERBOSE("Deallocated entity id: " << 
                     std::hex << 
                     i_id << 
                     " for type: " << 
                     get_entity_type(i_id));
                     
         if (map_it->second.empty()) m_type_id_map.erase(map_it);

         return i_id;
      }
   }

   return INVALID_ENTITY_ID;
}

void IdManager::deallocate_all_ids()
{
   m_type_id_map.clear();
}