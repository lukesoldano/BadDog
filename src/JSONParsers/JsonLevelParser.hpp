#pragma once

#include "ExtendedOptional.hpp"
#include "GameLevel.hpp"

#include <nlohmann/json.hpp>

namespace JSON
{
namespace LevelParser
{

   extended_opt<Game::Level> get_game_level_from_json(nlohmann::json i_json);

} // namespace LevelParser

} // namespace JSON
