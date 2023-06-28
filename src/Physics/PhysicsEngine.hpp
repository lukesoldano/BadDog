#pragma once

#include "CollisionDetector.hpp"

namespace Physics
{

// @warning This class is not thread safe
// @warning This class should not be sub-classed
class PhysicsEngine
{
public:

   PhysicsEngine() = default;
   ~PhysicsEngine() = default;

   void process();

private:

   CollisionDetector m_collision_detector;

};

} // namespace PhysicsEngine