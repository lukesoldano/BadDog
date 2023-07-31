#pragma once

#include "CollisionDetector.hpp"
#include "ILogicEngine.hpp"

namespace Physics
{

// @warning This class is not thread safe
class PhysicsEngine : public ILogicEngine
{
   CollisionDetector m_collision_detector;

public:

   PhysicsEngine() = default;
   virtual ~PhysicsEngine() = default;

   void initialize() override final;
   void teardown() override final;

   void process() override final;

};

} // namespace PhysicsEngine