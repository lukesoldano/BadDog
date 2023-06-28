#pragma once

#include "ProjectDefs.hpp"

namespace Physics
{
namespace Event
{

struct PlayerCollisionWithStaticEntity
{
   EntityId m_static_entity_id;
   Point m_collision_point;
};

} // namespace Event

} // namespace Physics