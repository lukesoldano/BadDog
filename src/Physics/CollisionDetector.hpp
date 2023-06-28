#pragma once

#include "PhysicsDefs.hpp"

#include "SDL_rect.h"

#include <optional>

namespace Physics
{

// @warning This class is not thread safe
class CollisionDetector
{
public:

   CollisionDetector() = default;
   virtual ~CollisionDetector() = default;

   // Returns nullopt if no collision, o/w xy position where collision would occur
   std::optional<XYPosition_t> check(const SDL_Rect& object1, 
                                     const SDL_Rect& object2, 
                                     const DisplacementVector_t& object1_displacement,
                                     const DisplacementVector_t& object2_displacement) const;

};

} // namespace Physics