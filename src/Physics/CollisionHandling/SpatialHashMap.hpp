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

// @note Any given entities height or width MUST be less than or equal to the height or width of
//       the cells owned by this map - neighboring entities are always assumed to be within the 
//       same cell and all adjacent cells, that breaks down if entities can spread across more 
//       than two cells horizontally or vertically
// @warning This class is not thread safe
template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
class SpatialHashMap
{
   static_assert(CELL_WIDTH != 0, "SpatialHashMap cannot have cells of width 0");
   static_assert(CELL_HEIGHT != 0, "SpatialHashMap cannot have cells of height 0");
   static_assert(LEVEL_WIDTH != 0, "SpatialHashMap must have a non-zero level width");
   static_assert(LEVEL_HEIGHT != 0, "SpatialHashMap must have at non-zero level height");
   static_assert(LEVEL_WIDTH % CELL_WIDTH == 0, "SpatialHashMap level width should be divisible by cell width");
   static_assert(LEVEL_HEIGHT % CELL_HEIGHT == 0, "SpatialHashMap level height should be divisible by cell height");

   std::array<std::set<EntityId>, (LEVEL_WIDTH / CELL_WIDTH) * (LEVEL_HEIGHT / CELL_HEIGHT)> m_cells;
   std::unordered_map<EntityId, SpatialHashMapCell_t> m_entity_cell_map;

public:

   SpatialHashMap() = default;
   virtual ~SpatialHashMap() = default;

   bool contains_entity(EntityId i_id) const;
   std::vector<EntityId> get_neighbors(EntityId i_id) const;
   std::vector<EntityId> get_neighbors(FRect i_area) const;

   std::optional<SpatialHashMapCell_t> add_entity(EntityId i_id, FPoint i_position);
   std::optional<SpatialHashMapCell_t> add_entity(EntityId i_id, FRect i_position);

   std::optional<SpatialHashMapCell_t> move_entity(EntityId i_id, FPoint i_position);
   std::optional<SpatialHashMapCell_t> move_entity(EntityId i_id, FRect i_position);

   std::optional<SpatialHashMapCell_t> remove_entity(EntityId i_id);

private:

   std::optional<SpatialHashMapCell_t> get_cell_for_position(Point i_position) const;
   std::optional<SpatialHashMapCell_t> get_cell_for_position(FPoint i_position) const;
   std::vector<SpatialHashMapCell_t> get_neighboring_cells(SpatialHashMapCell_t i_cell) const;

};

#include "SpatialHashMap.inl"
   
} // namespace Physics