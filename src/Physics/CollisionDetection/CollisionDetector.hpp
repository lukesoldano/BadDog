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
   std::optional<XYPosition> check(const SDL_Rect& object1, const SDL_Rect& object2) const;

};

} // namespace Physics