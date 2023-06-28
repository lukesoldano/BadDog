#include "TestLevel.hpp"

#include "SpatialHashMap.hpp"

using namespace Game;

namespace
{
   constexpr auto JSON_LEVEL_FILE_NAME = "TestLevel.json";

   std::filesystem::path get_json_path()
   {
      std::filesystem::path path(JSON_LEVEL_ASSETS_DIRECTORY);
      path.append(JSON_LEVEL_FILE_NAME);
      return path;
   }
}

TestLevel::TestLevel() :
   Level(get_json_path())
{

}