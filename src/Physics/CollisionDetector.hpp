// #pragma once

// #include "PhysicsDefs.hpp"
// #include "ProjectDefs.hpp"

// #include <optional>

// namespace Physics
// {

// struct RayVsRectCollision
// {
//    Vector2DFloat m_contact_point;
//    Vector2DFloat m_contact_normal;
//    float m_time_of_near_hit;
// };

// // @warning This class is not thread safe
// class CollisionDetector
// {
// public:

//    CollisionDetector() = default;
//    virtual ~CollisionDetector() = default;

//    bool are_aabbs_colliding(const FRect& object1, const FRect& object2) const;

//    std::optional<RayVsRectCollision> get_ray_vs_aabb_collision(const Vector2DFloat& ray_origin,
//                                                                const Vector2DFloat& ray_direction,
//                                                                const FRect& aabb) const;

// };

// } // namespace Physics