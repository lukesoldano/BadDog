#include <gtest/gtest.h>

#include "EntityUtilities.hpp"
#include "EntityUtilities.hpp"
#include "EntityTypes.hpp"

using namespace Entity;

TEST(EntityUtilities, StringToType)
{
   auto type_opt = get_entity_type_from_string("player_one");
   EXPECT_TRUE(type_opt.has_value());
   EXPECT_EQ(type_opt.value(), EntityType::player_one);

   type_opt = get_entity_type_from_string("player_two");
   EXPECT_TRUE(type_opt.has_value());
   EXPECT_EQ(type_opt.value(), EntityType::player_two);

   type_opt = get_entity_type_from_string("player_one_projectile");
   EXPECT_TRUE(type_opt.has_value());
   EXPECT_EQ(type_opt.value(), EntityType::player_one_projectile);

   type_opt = get_entity_type_from_string("player_two_projectile");
   EXPECT_TRUE(type_opt.has_value());
   EXPECT_EQ(type_opt.value(), EntityType::player_two_projectile);

   type_opt = get_entity_type_from_string("ai");
   EXPECT_TRUE(type_opt.has_value());
   EXPECT_EQ(type_opt.value(), EntityType::ai);

   type_opt = get_entity_type_from_string("ai_projectile");
   EXPECT_TRUE(type_opt.has_value());
   EXPECT_EQ(type_opt.value(), EntityType::ai_projectile);

   type_opt = get_entity_type_from_string("dynamic_object");
   EXPECT_TRUE(type_opt.has_value());
   EXPECT_EQ(type_opt.value(), EntityType::dynamic_object);

   type_opt = get_entity_type_from_string("static_object");
   EXPECT_TRUE(type_opt.has_value());
   EXPECT_EQ(type_opt.value(), EntityType::static_object);

   type_opt = get_entity_type_from_string("projectile_types");
   EXPECT_FALSE(type_opt.has_value());

   type_opt = get_entity_type_from_string("poop");
   EXPECT_FALSE(type_opt.has_value());
}

TEST(EntityUtilities, GetEntityTypeId)
{
   EntityId id = 0x000000F0FFFFFFFF;
   EXPECT_EQ(get_entity_type_id(id), 0xFFFFFFFF);

   id = 0xF0000000FFFFFFFE;
   EXPECT_EQ(get_entity_type_id(id), 0xFFFFFFFE);
}

TEST(EntityUtilities, GetEntityType)
{
   EntityId id = 0xFFFFFFFF00001100;
   EXPECT_EQ(static_cast<std::underlying_type_t<EntityType>>(get_entity_type(id)), 0xFFFFFFFF);

   id = 0xFFFFFFFE00400010;
   EXPECT_EQ(static_cast<std::underlying_type_t<EntityType>>(get_entity_type(id)), 0xFFFFFFFE);
}

TEST(EntityUtilities, IsEntityType)
{
   EntityId id = static_cast<EntityId>(EntityType::ai) << ENTITY_TYPE_SHIFT;
   id += 0x0000000F;
   EXPECT_TRUE(is_entity_type(id, EntityType::ai));
   EXPECT_FALSE(is_entity_type(id, EntityType::player_one));

   id = static_cast<EntityId>(EntityType::player_one) << ENTITY_TYPE_SHIFT;
   id += 0xF0000000;
   EXPECT_TRUE(is_entity_type(id, EntityType::player_one));
   EXPECT_FALSE(is_entity_type(id, EntityType::ai));
}

TEST(EntityUtilities, MasksForEntityType)
{
   EXPECT_TRUE(masks_for_entity_type(EntityType::ai, EntityType::ai));
   EXPECT_TRUE(masks_for_entity_type(EntityType::ai, EntityType::ai_types));
   EXPECT_FALSE(masks_for_entity_type(EntityType::ai, EntityType::player_one));
}

TEST(EntityUtilities, EntityTypeMasks)
{
   EXPECT_FALSE(masks_for_entity_type(EntityType::player_one, EntityType::player_two));

   EXPECT_TRUE(masks_for_entity_type(EntityType::player_one, EntityType::players));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_two, EntityType::players));

   EXPECT_TRUE(masks_for_entity_type(EntityType::player_one_projectile, EntityType::player_projectile_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_two_projectile, EntityType::player_projectile_types));

   EXPECT_TRUE(masks_for_entity_type(EntityType::player_one, EntityType::player_one_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_one_projectile, EntityType::player_one_types));

   EXPECT_TRUE(masks_for_entity_type(EntityType::player_two, EntityType::player_two_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_two_projectile, EntityType::player_two_types));

   EXPECT_FALSE(masks_for_entity_type(EntityType::ai_types, EntityType::player_types));
   EXPECT_FALSE(masks_for_entity_type(EntityType::object_types, EntityType::player_types));
   EXPECT_FALSE(masks_for_entity_type(EntityType::non_player_types, EntityType::player_types));

   EXPECT_TRUE(masks_for_entity_type(EntityType::player_types, EntityType::players));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_types, EntityType::player_projectile_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_types, EntityType::player_one_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_types, EntityType::player_one_projectile));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_types, EntityType::player_two_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_types, EntityType::player_two_projectile));

   EXPECT_TRUE(masks_for_entity_type(EntityType::ai, EntityType::ai_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::ai_projectile, EntityType::ai_types));

   EXPECT_TRUE(masks_for_entity_type(EntityType::player_one_projectile, EntityType::projectile_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::player_two_projectile, EntityType::projectile_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::ai_projectile, EntityType::projectile_types));

   EXPECT_FALSE(masks_for_entity_type(EntityType::dynamic_object, EntityType::static_object));

   EXPECT_TRUE(masks_for_entity_type(EntityType::dynamic_object, EntityType::object_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::static_object, EntityType::object_types));

   EXPECT_FALSE(masks_for_entity_type(EntityType::players, EntityType::non_player_types));
   EXPECT_FALSE(masks_for_entity_type(EntityType::player_projectile_types, EntityType::non_player_types));
   EXPECT_FALSE(masks_for_entity_type(EntityType::player_types, EntityType::non_player_types));

   EXPECT_TRUE(masks_for_entity_type(EntityType::ai, EntityType::non_player_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::ai_projectile, EntityType::non_player_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::dynamic_object, EntityType::non_player_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::static_object, EntityType::non_player_types));

   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::players));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::player_projectile_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::player_one_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::player_one_projectile));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::player_two_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::player_two_projectile));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::player_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::ai));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::ai_projectile));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::dynamic_object));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::static_object));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::object_types));
   EXPECT_TRUE(masks_for_entity_type(EntityType::all_types, EntityType::non_player_types));
}