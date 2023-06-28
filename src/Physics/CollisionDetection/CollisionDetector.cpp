#include "CollisionDetector.hpp"

using namespace Physics;

std::optional<XYPosition> CollisionDetector::check(const SDL_Rect& object1, 
                                                     const SDL_Rect& object2) const
{
   // TODO This is, how you say, "garbage"
   if ((object1.x + object1.w) >= object2.x)
   {
      return XYPosition{object2.x - object1.w-1, object1.y};
   }

   return std::nullopt;
}