#include "GameLevelLoader.hpp"

#include "JsonFileReader.hpp"
#include "ProjectMacros.hpp"

using namespace Game;

namespace
{
   void log_failed_key_error(const std::filesystem::path& i_json_path, auto&& i_key)
   {
      LOG_ERROR("Failed to get " << i_key << " from json file: " << i_json_path.string());
   };

   bool get_spatial_hash_map_settings(const std::filesystem::path& i_json_path,
                                      const JSON::json& i_json_object, 
                                      Pixels& o_shm_cell_width,
                                      Pixels& o_shm_cell_height)
   {
      using namespace JSON;

      constexpr auto SPATIAL_HASH_MAP_KEY = "spatial_hash_map_settings";
      json spatial_hash_map_json;
      if (! get_json_value(i_json_object, SPATIAL_HASH_MAP_KEY, spatial_hash_map_json) ||
          ! spatial_hash_map_json.is_object())
      {
         log_failed_key_error(i_json_path, SPATIAL_HASH_MAP_KEY);
         return false;
      } 

      constexpr auto SPATIAL_HASH_MAP_CELL_WIDTH_KEY = "cell_width";
      if (! get_json_value(spatial_hash_map_json, 
                           SPATIAL_HASH_MAP_CELL_WIDTH_KEY, 
                           o_shm_cell_width))
      {
         log_failed_key_error(i_json_path, SPATIAL_HASH_MAP_CELL_WIDTH_KEY);
         return false;
      }

      constexpr auto SPATIAL_HASH_MAP_CELL_HEIGHT_KEY = "cell_height";
      if (! get_json_value(spatial_hash_map_json, 
                           SPATIAL_HASH_MAP_CELL_HEIGHT_KEY, 
                           o_shm_cell_height))
      {
         log_failed_key_error(i_json_path, SPATIAL_HASH_MAP_CELL_HEIGHT_KEY);
         return false;
      }

      return true;
   }

   bool get_player_entities(const std::filesystem::path& i_json_path,
                            const JSON::json& i_json_object, 
                            Level& io_level)
   {
      return true;
   }

} // anonymous namespace

extended_opt<Level> LevelLoader::load_from_json(const std::filesystem::path& i_json_path)
{
   using namespace JSON;

   const auto json_file_pair = FileReader::read_json_file(i_json_path);
   CHECK_CONDITION_RETURN_VALUE(json_file_pair.has_value(), std::nullopt);

   const auto& json_object = json_file_pair.value().second;

   Level level;

   constexpr auto LEVEL_NAME_KEY = "level_name";
   if (! get_json_value(json_object, LEVEL_NAME_KEY, level.m_name))
   {
      log_failed_key_error(i_json_path, LEVEL_NAME_KEY);
      return std::nullopt;
   } 

   constexpr auto LEVEL_DIMMENSIONS_KEY = "level_dimmensions";
   if (! get_json_value(json_object, LEVEL_DIMMENSIONS_KEY, level.m_dimmensions))
   {
      log_failed_key_error(i_json_path, LEVEL_DIMMENSIONS_KEY);
      return std::nullopt;
   }

   Pixels shm_cell_width;
   Pixels shm_cell_height;
   if (! get_spatial_hash_map_settings(i_json_path, json_object, shm_cell_width, shm_cell_height))
   {
      LOG_ERROR("Failed to build spatial hash map settings from json file: " << 
                i_json_path.string());
      return std::nullopt;
   }

   level.m_spatial_hash_map = SpatialHashMap{level.m_dimmensions.m_width, 
                                             level.m_dimmensions.m_height, 
                                             shm_cell_width,
                                             shm_cell_height};

   if (! get_player_entities(i_json_path, json_object, level))
   {
      LOG_ERROR("Failed to build player entities from json file: " << 
                i_json_path.string());
      return std::nullopt;
   }

   return level;
}