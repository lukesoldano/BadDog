#include "CollisionDetector.hpp"

using namespace Physics;

bool CollisionDetector::are_aabbs_colliding(const SDL_FRect& object1, 
                                            const SDL_FRect& object2) const 
{ 
   if (object1.x <= object2.x)
   {
      if (object1.x + object1.w <= object2.x) return false;
   }
   else
   {
      if (object1.x >= object2.x + object2.w) return false;
   }

   // The x's are overlapping, check y
   if (object1.y <= object2.y)
   {
      if (object1.y + object1.h <= object2.y) return false;
   }
   else
   {
      if (object1.y >= object2.y + object2.h) return false;
   }

   return true;
}

std::optional<RayVsRectCollision> CollisionDetector::get_ray_vs_aabb_collision(const Vector2DFloat& ray_origin,
                                                                               const Vector2DFloat& ray_direction,
                                                                               const SDL_FRect& aabb) const
{
   std::optional<RayVsRectCollision> collision_info;

   

   return collision_info;
}