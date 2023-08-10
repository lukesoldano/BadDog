#pragma once

#include "ExtendedOptional.hpp"
#include "GameLevel.hpp"

#include <filesystem>
#include <optional>

namespace Game
{
namespace LevelLoader
{

extended_opt<Level> load_from_json(const std::filesystem::path& i_json_path);

} // namespace LevelLoader

} // namespace Game