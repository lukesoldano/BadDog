#pragma once

#include "PhysicsDefs.hpp"
#include "ProjectDefs.hpp"

#include <array>
#include <optional>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <vector>

namespace Physics
{

using SpatialHashMapCell_t = size_t;

// @note The i_cell areas should be larger than the area of the largest entity in order to take 
//       advantage of this container as an optimization for broad phase collision detection
// @warning This class is not thread safe
template <size_t X_CELLS, size_t Y_CELLS, size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT>
class SpatialHashMap
{
   static_assert(X_CELLS != 0, "SpatialHashMap must have at least one x-i_cell");
   static_assert(Y_CELLS != 0, "SpatialHashMap must have at least one y-i_cell");
   static_assert(LEVEL_WIDTH != 0, "SpatialHashMap must have a non-zero LEVEL_WIDTH");
   static_assert(LEVEL_HEIGHT != 0, "SpatialHashMap must have at non-zero LEVEL_HEIGHT");
   static_assert(LEVEL_WIDTH % X_CELLS == 0, "SpatialHashMap LEVEL_WIDTH should be divisible by # of x-cells");
   static_assert(LEVEL_HEIGHT % Y_CELLS == 0, "SpatialHashMap LEVEL_HEIGHT should be divisible by # of y-cells");

   std::array<std::set<EntityId>, X_CELLS * Y_CELLS> m_cells;
   std::unordered_map<EntityId, SpatialHashMapCell_t> m_entity_cell_map;

public:

   SpatialHashMap() = default;
   virtual ~SpatialHashMap() = default;

   bool contains_entity(EntityId i_id) const;
   std::vector<EntityId> get_neighbors(EntityId i_id) const;

   std::optional<SpatialHashMapCell_t> add_entity(EntityId i_id, FPoint i_position);
   std::optional<SpatialHashMapCell_t> add_entity(EntityId i_id, FRect i_position);

   std::optional<SpatialHashMapCell_t> move_entity(EntityId i_id, FPoint i_position);
   std::optional<SpatialHashMapCell_t> move_entity(EntityId i_id, FRect i_position);

   std::optional<SpatialHashMapCell_t> remove_entity(EntityId i_id);

private:

   std::optional<SpatialHashMapCell_t> get_cell_for_position(FPoint i_position) const;
   std::vector<SpatialHashMapCell_t> get_neighboring_cells(SpatialHashMapCell_t i_cell) const;

};

#include "SpatialHashMap.inl"
   
} // namespace Physics