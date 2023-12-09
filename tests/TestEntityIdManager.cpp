#include <gtest/gtest.h>

#include "EntityIdManager.hpp"
#include "EntityUtilities.hpp"
#include "EntityTypes.hpp"

using namespace Entity;

TEST(EntityIdManager, Singleton) 
{
   ASSERT_NE(nullptr, &IdManager::instance());
}

TEST(EntityIdManager, AllocateId)
{
   auto& manager = IdManager::instance();

   auto id = manager.allocate_id(EntityType::player_one);
   EXPECT_EQ(get_entity_type(id), EntityType::player_one);
   EXPECT_EQ(PLAYER_ONE_ENTITY_ID, id);
   EXPECT_EQ(PLAYER_ONE_ENTITY_ID, manager.allocate_id(EntityType::player_one));
   EXPECT_TRUE(manager.is_id_allocated(id));
 
   id = manager.allocate_id(EntityType::player_two);
   EXPECT_EQ(get_entity_type(id), EntityType::player_two);
   EXPECT_EQ(PLAYER_TWO_ENTITY_ID, id);
   EXPECT_EQ(PLAYER_TWO_ENTITY_ID, manager.allocate_id(EntityType::player_two));
   EXPECT_TRUE(manager.is_id_allocated(id));

   id = manager.allocate_id(EntityType::player_one_projectile);
   EXPECT_EQ(get_entity_type(id), EntityType::player_one_projectile);
   EXPECT_TRUE(manager.is_id_allocated(id));


   EXPECT_NE(id, manager.allocate_id(EntityType::player_one_projectile));
   EXPECT_NE(id, manager.allocate_id(EntityType::player_one_projectile));

   id = manager.allocate_id(EntityType::player_two_projectile);
   EXPECT_EQ(get_entity_type(id), EntityType::player_two_projectile);
   EXPECT_TRUE(manager.is_id_allocated(id));
   
   EXPECT_NE(id, manager.allocate_id(EntityType::player_two_projectile));
   EXPECT_NE(id, manager.allocate_id(EntityType::player_two_projectile));

   id = manager.deallocate_id(PLAYER_ONE_ENTITY_ID);
   EXPECT_EQ(PLAYER_ONE_ENTITY_ID, id);
   EXPECT_EQ(INVALID_ENTITY_ID, manager.deallocate_id(PLAYER_ONE_ENTITY_ID));

   id = manager.deallocate_id(PLAYER_TWO_ENTITY_ID);
   EXPECT_EQ(PLAYER_TWO_ENTITY_ID, id);
   EXPECT_EQ(INVALID_ENTITY_ID, manager.deallocate_id(PLAYER_TWO_ENTITY_ID));

   id = manager.allocate_id(EntityType::player_one_projectile);
   EXPECT_EQ(get_entity_type(id), EntityType::player_one_projectile);
   EXPECT_NE(id, INVALID_ENTITY_ID);
   EXPECT_TRUE(manager.is_id_allocated(id));
   EXPECT_EQ(id, manager.deallocate_id(id));
   EXPECT_EQ(INVALID_ENTITY_ID, manager.deallocate_id(id));
}

TEST(EntityIdManager, DeallocateAllIds)
{
   auto& manager = IdManager::instance();

   EXPECT_NE(INVALID_ENTITY_ID, manager.allocate_id(EntityType::player_one));
   EXPECT_NE(INVALID_ENTITY_ID, manager.allocate_id(EntityType::player_two));
   EXPECT_NE(INVALID_ENTITY_ID, manager.allocate_id(EntityType::player_one_projectile));
   EXPECT_NE(INVALID_ENTITY_ID, manager.allocate_id(EntityType::player_two_projectile));

   manager.deallocate_all_ids();

   EXPECT_NE(INVALID_ENTITY_ID, manager.allocate_id(EntityType::player_one));
   EXPECT_NE(INVALID_ENTITY_ID, manager.allocate_id(EntityType::player_two));
   EXPECT_NE(INVALID_ENTITY_ID, manager.allocate_id(EntityType::player_one_projectile));
   EXPECT_NE(INVALID_ENTITY_ID, manager.allocate_id(EntityType::player_two_projectile));
}