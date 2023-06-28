#pragma once

#include "PhysicsDefs.hpp"

namespace Physics
{

// @warning This class is not thread safe
class CollisionDetector
{
public:

   CollisionDetector() = default;
   virtual ~CollisionDetector() = default;

   bool check(SDL_FRect object1, SDL_FRect object2);

};

} // namespace Physics