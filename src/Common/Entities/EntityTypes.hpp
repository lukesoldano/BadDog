#pragma once

using EntityId = uint64_t;

enum class EntityType : uint32_t
{
   player_one = 0x0000000F,
   player_two = 0x000000F0,
   player_one_projectile = 0x00000F00,
   player_two_projectile = 0x0000F000,
   player_one_types = 0x00000F0F,
   player_two_types = 0x0000F0F0,
   players = 0x000000FF,
   player_projectile_types = 0x0000FF00,
   player_types = 0x0000FFFF,
   ai = 0x000F0000,
   ai_projectile = 0x00F00000,
   ai_types = 0x00FF0000,
   projectile_types = 0x00F0FF00,
   dynamic_object = 0x0F000000,
   static_object = 0xF0000000,
   object_types = 0xFF000000,
   non_player_types = 0xFFFF0000,
   all_types = 0xFFFFFFFF
};