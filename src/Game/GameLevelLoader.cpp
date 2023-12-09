#include "GameLevelLoader.hpp"

#include "EntityIdManager.hpp"
#include "ProjectMacros.hpp"

#define LOG_KEY_ERROR(key) \
   LOG_ERROR("Failed to get " << key << " from json file: " << m_current_json_file.to_string()); 

#define GET_JSON_VALUE_RETURN_ON_ERROR(json_object, key, value, return_value) \
   if (! JSON::get_json_value(json_object, key, value)) \
   { \
      LOG_KEY_ERROR(key); \
      return return_value; \
   }

using namespace Game;

extended_opt<Level> LevelLoader::load_from_json(const std::filesystem::path& i_json_path)
{
   using namespace JSON;

   auto json_file_pair = FileReader::read_json_file(i_json_path);
   CHECK_CONDITION_RETURN_VALUE(json_file_pair.has_value(), std::nullopt);

   m_current_json_file = std::move(json_file_pair.value().first);
   m_loaded_json = std::move(json_file_pair.value().second);

   Level level;

   constexpr auto LEVEL_NAME_KEY = "level_name";
   GET_JSON_VALUE_RETURN_ON_ERROR(m_loaded_json, LEVEL_NAME_KEY, level.m_name, std::nullopt);

   constexpr auto LEVEL_DIMMENSIONS_KEY = "level_dimmensions";
   GET_JSON_VALUE_RETURN_ON_ERROR(m_loaded_json, 
                                  LEVEL_DIMMENSIONS_KEY, 
                                  level.m_dimmensions, 
                                  std::nullopt);

   if (! get_spatial_hash_map(level))
   {
      LOG_ERROR("Failed to build spatial hash map from json file: " << 
                i_json_path.string());
      return std::nullopt;
   }

   if (! get_player_entities(level))
   {
      LOG_ERROR("Failed to build player entities from json file: " << 
                i_json_path.string());
      return std::nullopt;
   }

   return level;
}

bool LevelLoader::get_spatial_hash_map(Level& io_level) const
{
   using namespace JSON;

   constexpr auto SPATIAL_HASH_MAP_KEY = "spatial_hash_map_settings";
   json spatial_hash_map_json;
   GET_JSON_VALUE_RETURN_ON_ERROR(m_loaded_json, 
                                  SPATIAL_HASH_MAP_KEY, 
                                  spatial_hash_map_json, 
                                  false);

   constexpr auto SPATIAL_HASH_MAP_CELL_WIDTH_KEY = "cell_width";
   Pixels shm_cell_width = 0;
   GET_JSON_VALUE_RETURN_ON_ERROR(spatial_hash_map_json, 
                                  SPATIAL_HASH_MAP_CELL_WIDTH_KEY, 
                                  shm_cell_width, 
                                  false);

   constexpr auto SPATIAL_HASH_MAP_CELL_HEIGHT_KEY = "cell_height";
   Pixels shm_cell_height = 0;
   GET_JSON_VALUE_RETURN_ON_ERROR(spatial_hash_map_json, 
                                  SPATIAL_HASH_MAP_CELL_HEIGHT_KEY, 
                                  shm_cell_height, 
                                  false);

   io_level.m_spatial_hash_map = SpatialHashMap{io_level.m_dimmensions.m_width, 
                                                io_level.m_dimmensions.m_height, 
                                                shm_cell_width,
                                                shm_cell_height};

   return true;
}

bool LevelLoader::get_entity_traits(const EntityId& i_id, 
                                    const JSON::json& i_json, 
                                    Level& io_level) const
{
   constexpr auto POSITIONABLE_TRAIT_KEY = "positionable";
   constexpr auto COLLIDABLE_TRAIT_KEY = "collidable";
   constexpr auto MOVEABLE_TRAIT_KEY = "moveable";
   constexpr auto STATUS_EFFECTABLE_TRAIT_KEY = "status_effectable";
   constexpr auto DRAWABLE_TRAIT_KEY = "drawable";
   constexpr auto ANIMATEABLE_TRAIT_KEY = "animateable";

   CHECK_CONDITION_RETURN_VALUE(i_json.is_object(), false);

   bool success = true;

   bool positionable = false;
   for (const auto& trait : i_json.items())
   {
      if (POSITIONABLE_TRAIT_KEY == trait.key())
      {
         if (! trait.value().is_array() || 2 != trait.value().size())
         {
            LOG_ERROR("Positionable trait must be an array with two values - [x, y]");
            success = false;
            break;
         }

         positionable = true;
         io_level.m_positionable_entities.emplace(i_id, FPosition{trait.value()[0], trait.value()[1]});
      }
   }

   if (success)
   { 
      if (positionable)
      {

      }
   }

   return success;
}

bool LevelLoader::get_entity(const EntityId& i_id, const JSON::json& i_json, Level& io_level) const
{
   using namespace JSON;

   CHECK_CONDITION_RETURN_VALUE(i_json.is_object(), false);

   constexpr auto ENTITY_NAME_KEY = "name";
   std::string name;
   GET_JSON_VALUE_RETURN_ON_ERROR(i_json, ENTITY_NAME_KEY, name, false);

   io_level.m_named_entities.emplace(i_id, name);

   constexpr auto TRAITS_KEY = "traits";
   json traits_json;
   GET_JSON_VALUE_RETURN_ON_ERROR(i_json, 
                                  TRAITS_KEY, 
                                  traits_json, 
                                  false);

   if (! get_entity_traits(i_id, traits_json, io_level))
   {
      LOG_ERROR("Failed to build traits for entity with id: " << std::hex << i_id);
      return false;
   }

   return true;
}

bool LevelLoader::get_player_entities(Level& io_level) const
{
   using namespace JSON;

   constexpr auto PLAYER_ONE_ENTITY_KEY = "player_one_entity";
   json player_one_entity_json;
   GET_JSON_VALUE_RETURN_ON_ERROR(m_loaded_json, 
                                  PLAYER_ONE_ENTITY_KEY, 
                                  player_one_entity_json, 
                                  false);

   constexpr auto PLAYER_TWO_ENTITY_KEY = "player_two_entity";
   json player_two_entity_json;
   GET_JSON_VALUE_RETURN_ON_ERROR(m_loaded_json, 
                                  PLAYER_TWO_ENTITY_KEY, 
                                  player_two_entity_json, 
                                  false);

   const auto player_one_id = Entity::IdManager::instance().allocate_id(EntityType::player_one);
   if (INVALID_ENTITY_ID != player_one_id &&
       ! get_entity(player_one_id, player_one_entity_json, io_level))
   {
      io_level.clear_entity(player_one_id);
      Entity::IdManager::instance().deallocate_id(player_one_id);

      LOG_ERROR("Failed to build player one entity");
      return false;
   }

   const auto player_two_id = Entity::IdManager::instance().allocate_id(EntityType::player_two);
   if (INVALID_ENTITY_ID != player_two_id &&
       ! get_entity(player_two_id, player_two_entity_json, io_level))
   {
      io_level.clear_entity(player_one_id);
      Entity::IdManager::instance().deallocate_id(player_one_id);

      io_level.clear_entity(player_two_id);
      Entity::IdManager::instance().deallocate_id(player_two_id);

      LOG_ERROR("Failed to build player two entity");
      return false;
   }

   return true;
}