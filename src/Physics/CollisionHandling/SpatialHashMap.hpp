#pragma once

#include "ExtendedOptional.hpp"
#include "ProjectDefs.hpp"

#include <set>
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
class SpatialHashMap
{
   size_t m_level_width;
   size_t m_level_height;
   size_t m_cell_width;
   size_t m_cell_height;
   size_t m_num_x_cells;
   size_t m_num_y_cells;

   std::vector<std::set<EntityId>> m_cells;
   std::unordered_map<EntityId, SpatialHashMapCell_t> m_entity_cell_map;

public:

   SpatialHashMap() = delete;
   SpatialHashMap(size_t i_level_width, 
                  size_t i_level_height, 
                  size_t i_cell_width, 
                  size_t i_cell_height) noexcept;
   virtual ~SpatialHashMap() noexcept = default;

   size_t get_width() const { return m_level_width; }
   size_t get_height() const { return m_level_height; }
   size_t get_cell_width() const { return m_cell_width; }
   size_t get_cell_height() const { return m_cell_height; }

   bool contains_entity(EntityId i_id) const;
   std::vector<EntityId> get_neighbors(EntityId i_id) const;
   std::vector<EntityId> get_neighbors(FRect i_area) const;

   extended_opt<SpatialHashMapCell_t> add_entity(EntityId i_id, FPoint i_position);
   extended_opt<SpatialHashMapCell_t> add_entity(EntityId i_id, FRect i_position);

   extended_opt<SpatialHashMapCell_t> move_entity(EntityId i_id, FPoint i_position);
   extended_opt<SpatialHashMapCell_t> move_entity(EntityId i_id, FRect i_position);

   extended_opt<SpatialHashMapCell_t> remove_entity(EntityId i_id);

private:

   extended_opt<SpatialHashMapCell_t> get_cell_for_position(Point i_position) const;
   extended_opt<SpatialHashMapCell_t> get_cell_for_position(FPoint i_position) const;
   std::vector<SpatialHashMapCell_t> get_neighboring_cells(SpatialHashMapCell_t i_cell) const;
   std::vector<SpatialHashMapCell_t> get_neighboring_cells(const Rect& i_frame) const;

};
   
} // namespace Physics