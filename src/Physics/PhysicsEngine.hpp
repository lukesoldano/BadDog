#pragma once

#include "CollisionDetector.hpp"
#include "CollisionResolver.hpp"
#include "ILogicEngine.hpp"

namespace Physics
{

// @warning This class is not thread safe
class PhysicsEngine : public ILogicEngine
{
   CollisionDetector m_collision_detector;
   CollisionResolver m_collision_resolver;

public:

   PhysicsEngine() = default;
   virtual ~PhysicsEngine() = default;

   void initialize() override final;
   void teardown() override final;

   void process() override final;

};

} // namespace PhysicsEngine