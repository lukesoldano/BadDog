#pragma once

#include "CollisionDetector.hpp"
#include "CollisionResolver.hpp"
#include "GameSettings.hpp"
#include "ILogicEngine.hpp"
#include "SpatialHashMap.hpp"

namespace Physics
{

// @warning This class is not thread safe
class PhysicsEngine : public ILogicEngine
{
   SpatialHashMap<20, 20, DEFAULT_LEVEL_WIDTH, DEFAULT_LEVEL_HEIGHT> m_spatial_hash_map;
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