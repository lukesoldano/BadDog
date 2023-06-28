#pragma once

#include "CollisionDetector.hpp"
#include "CollisionResolver.hpp"
#include "ILogicEngine.hpp"
#include "SpatialHashMap.hpp"

namespace Physics
{

// @warning This class is not thread safe
class PhysicsEngine : public ILogicEngine
{
   SpatialHashMap<7, 5, 700, 500> m_spatial_hash_map;
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