#pragma once

#include "EntityTypes.hpp"
#include "ExtendedOptional.hpp"
#include "GameLevel.hpp"
#include "JsonFileReader.hpp"

#include <filesystem>
#include <optional>

namespace Game
{

class LevelLoader
{
   JSON::FileInfo m_current_json_file;
   JSON::json m_loaded_json;

public:

   LevelLoader() = default;
   virtual ~LevelLoader() = default;

   extended_opt<Level> load_from_json(const std::filesystem::path& i_json_path);

private:

   bool get_spatial_hash_map(Level& io_level) const;
   bool get_entity_traits(const EntityId& i_id, const JSON::json& i_json, Level& io_level) const;
   bool get_entity(const EntityId& i_id, const JSON::json& i_json, Level& io_level) const;
   bool get_player_entities(Level& io_level) const;

};

} // namespace Game