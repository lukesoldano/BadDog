#include "JsonLevelParser.hpp"

#include "GameEntityDefs.hpp"
#include "JsonDefs.hpp"
#include "JsonUtilities.hpp" 

#include <assert.h>
#include <vector>

using namespace Game;
using namespace JSON;

namespace
{

extended_opt<StaticEntity> get_static_rect_entity_from_json(nlohmann::json i_json, bool i_visible)
{
   CHECK_JSON_OBJECT_RETURN_NULLOPT(i_json);

   std::string label;
   int x;
   int y;
   int width;
   int height;
   std::string color;

   // Silent failures possible
   Utilities::get_json_value(i_json, Keys::STATIC_ENTITY_LABEL, label);
   Utilities::get_json_value(i_json, Keys::STATIC_ENTITY_X, x);
   Utilities::get_json_value(i_json, Keys::STATIC_ENTITY_Y, y);
   Utilities::get_json_value(i_json, Keys::STATIC_ENTITY_RECT_WIDTH, width);
   Utilities::get_json_value(i_json, Keys::STATIC_ENTITY_RECT_HEIGHT, height);
   Utilities::get_json_value(i_json, Keys::STATIC_ENTITY_RECT_COLOR, color);

   return StaticEntity(i_visible,
                       std::move(label),
                       RectEntity{string_to_color(color), Rect{ x, y, width, height} });
}

std::vector<StaticEntity> get_static_entities_from_json(nlohmann::json i_json)
{
   CHECK_JSON_OBJECT_RETURN_EMPTY_INITIALIZER(i_json);

   const auto static_entities_it = i_json.find(Keys::LEVEL_STATIC_ENTITIES_ARRAY); 
   if (static_entities_it == i_json.end()) return {}; 
   const auto static_entities_json = *static_entities_it;

   // It's okay if there isn't a static entity array, but it has to be an array if it exists
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(static_entities_json.is_array());

   std::vector<StaticEntity> static_entities;
   for (const auto& static_entity_json : static_entities_json)
   {
      if (static_entity_json.is_null() || !static_entity_json.is_object()) continue;

      if (!static_entity_json.contains(Keys::STATIC_ENTITY_TYPE))
      {
         assert(false && "Static entity does not contain a type");
         LOG_ERROR("Static entity does not contain a type, skipping");
         continue;
      } 

      const auto instances_it = static_entity_json.find(Keys::STATIC_ENTITY_INSTANCES_ARRAY);
      if (instances_it == static_entity_json.end()) continue;
      const auto instances_json = *instances_it;

      std::string type;
      bool visible = false;

      // Silent failures possible
      Utilities::get_json_value(static_entity_json, Keys::STATIC_ENTITY_TYPE, type);
      Utilities::get_json_value(static_entity_json, Keys::STATIC_ENTITY_VISIBILITY, visible);

      if (Values::STATIC_ENTITY_RECT_TYPE == type)
      {
         for (const auto& instance_json : instances_json)
         {
            if (instance_json.is_null() || !instance_json.is_object()) continue;
            auto rect_entity = get_static_rect_entity_from_json(instance_json, visible);
            if (rect_entity.has_value()) static_entities.emplace_back(std::move(rect_entity.value()));
         }
      }
      else
      {
         assert(false && "Invalid static entity type");
         LOG_ERROR("Invalid static entity type, skipping");
         break;
      }

   }

   return static_entities;
}

} // namespace

extended_opt<Game::Level> LevelParser::get_game_level_from_json(nlohmann::json i_json)
{
   CHECK_JSON_OBJECT_RETURN_NULLOPT(i_json);
   
   auto it = i_json.find(Keys::LEVEL_INFO_OBJECT); 
   CHECK_CONDITION_RETURN_NULLOPT(it != i_json.end()); 
   auto level_info_json = *it;

   std::string name;
   size_t width;
   size_t height;
   size_t border_width;

   CHECK_CONDITION_RETURN_NULLOPT(Utilities::get_json_value(level_info_json, Keys::LEVEL_NAME, name));
   CHECK_CONDITION_RETURN_NULLOPT(Utilities::get_json_value(level_info_json, Keys::LEVEL_WIDTH, width));
   CHECK_CONDITION_RETURN_NULLOPT(Utilities::get_json_value(level_info_json, Keys::LEVEL_HEIGHT, height));
   CHECK_CONDITION_RETURN_NULLOPT(Utilities::get_json_value(level_info_json, Keys::LEVEL_BORDER_WIDTH, border_width));

   auto static_entities = get_static_entities_from_json(level_info_json);

   return Game::Level{std::move(name), width, height, border_width, std::move(static_entities)};
}