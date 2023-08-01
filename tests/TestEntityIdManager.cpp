#include <gtest/gtest.h>

#include "EntityIdManager.hpp"
#include "EntityTypes.hpp"

TEST(EntityIdManager, EntityTypeMasks)
{
   auto entity_types_overlap = [](auto type_one, auto type_two)
   {
      return static_cast<uint32_t>(type_one) & static_cast<uint32_t>(type_two);
   };

   EXPECT_FALSE(entity_types_overlap(EntityType::player_one, EntityType::player_two));

   EXPECT_TRUE(entity_types_overlap(EntityType::player_one, EntityType::players));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_two, EntityType::players));

   EXPECT_TRUE(entity_types_overlap(EntityType::player_one_projectile, EntityType::player_projectile_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_two_projectile, EntityType::player_projectile_types));

   EXPECT_TRUE(entity_types_overlap(EntityType::player_one, EntityType::player_one_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_one_projectile, EntityType::player_one_types));

   EXPECT_TRUE(entity_types_overlap(EntityType::player_two, EntityType::player_two_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_two_projectile, EntityType::player_two_types));

   EXPECT_FALSE(entity_types_overlap(EntityType::ai_types, EntityType::player_types));
   EXPECT_FALSE(entity_types_overlap(EntityType::object_types, EntityType::player_types));
   EXPECT_FALSE(entity_types_overlap(EntityType::non_player_types, EntityType::player_types));

   EXPECT_TRUE(entity_types_overlap(EntityType::player_types, EntityType::players));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_types, EntityType::player_projectile_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_types, EntityType::player_one_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_types, EntityType::player_one_projectile));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_types, EntityType::player_two_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_types, EntityType::player_two_projectile));

   EXPECT_TRUE(entity_types_overlap(EntityType::ai, EntityType::ai_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::ai_projectile, EntityType::ai_types));

   EXPECT_TRUE(entity_types_overlap(EntityType::player_one_projectile, EntityType::projectile_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::player_two_projectile, EntityType::projectile_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::ai_projectile, EntityType::projectile_types));

   EXPECT_FALSE(entity_types_overlap(EntityType::dynamic_object, EntityType::static_object));

   EXPECT_TRUE(entity_types_overlap(EntityType::dynamic_object, EntityType::object_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::static_object, EntityType::object_types));

   EXPECT_FALSE(entity_types_overlap(EntityType::players, EntityType::non_player_types));
   EXPECT_FALSE(entity_types_overlap(EntityType::player_projectile_types, EntityType::non_player_types));
   EXPECT_FALSE(entity_types_overlap(EntityType::player_types, EntityType::non_player_types));

   EXPECT_TRUE(entity_types_overlap(EntityType::ai, EntityType::non_player_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::ai_projectile, EntityType::non_player_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::dynamic_object, EntityType::non_player_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::static_object, EntityType::non_player_types));

   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::players));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::player_projectile_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::player_one_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::player_one_projectile));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::player_two_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::player_two_projectile));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::player_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::ai));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::ai_projectile));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::dynamic_object));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::static_object));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::object_types));
   EXPECT_TRUE(entity_types_overlap(EntityType::all_types, EntityType::non_player_types));
}

TEST(EntityIdManager, Singleton) 
{
   ASSERT_NE(nullptr, &EntityIdManager::instance());
}

// TEST(EntityIdManager, AllocateId)
// {
   // auto& manager = EntityIdManager::instance();

   // auto do_type_bytes_match = [](const EntityType type, const EntityId& id)
   // {
   //    return static_cast<EntityId>(type) == (EntityId & ENTITY_TYPE_MASK);
   // };

   // auto id = manager.allocate_id(EntityType::player_one);
   // EXPECT_TRUE(do_type_bytes_match(EntityType::player_one, id);
   // EXPECT_EQ(EntityType::PLAYER_ONE_ENTITY_ID, id);
 
   // id = manager.allocate_id(EntityType::player_two);
   // EXPECT_TRUE(do_type_bytes_match(EntityType::player_two, id);
   // EXPECT_EQ(EntityType::PLAYER_TWO_ENTITY_ID, id);

   // id = manager.allocate_id(EntityType::player_one_projectile);
   // EXPECT_TRUE(do_type_bytes_match(EntityType::player_one_projectile, id);

   // EXPECT_NE(id, manager.allocate_id(EntityType::player_one_projectile));
   // EXPECT_NE(id, manager.allocate_id(EntityType::player_one_projectile));

   // id = manager.allocate_id(EntityType::player_two_projectile);
   // EXPECT_TRUE(do_type_bytes_match(EntityType::player_two_projectile, id);
   
   // EXPECT_NE(id, manager.allocate_id(EntityType::player_two_projectile));
   // EXPECT_NE(id, manager.allocate_id(EntityType::player_two_projectile));
// }