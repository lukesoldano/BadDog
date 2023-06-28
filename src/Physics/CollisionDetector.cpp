#include "CollisionDetector.hpp"

using namespace Physics;

std::optional<XYPosition_t> CollisionDetector::check(const SDL_Rect& object1, 
                                                     const SDL_Rect& object2, 
                                                     const DisplacementVector_t& object1_displacement,
                                                     const DisplacementVector_t& object2_displacement) const
{
   if ((object1.x + object1.w) + object1_displacement.first >= object2.x)
   {
      return XYPosition_t{object2.x - object1.w, object1.y + object1_displacement.second};
   }

   return std::nullopt;
}