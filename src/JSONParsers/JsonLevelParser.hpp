#pragma once

#include "GameLevel.hpp"
#include "JsonDefs.hpp"

#include <filesystem>
#include <optional>

namespace JSON
{
namespace LevelParser
{

   std::optional<Game::Level> get_game_level_from_json(nlohmann::json i_json);

} // namespace LevelParser

} // namespace JSON
