#pragma once

#include "EntityTypes.hpp"
#include "ExtendedOptional.hpp"
#include "ProjectTypes.hpp"

#include <set>
#include <unordered_map>
#include <vector>

// @note Any given entities height or width MUST be less than or equal to the height or width of
//       the cells owned by this map - neighboring entities are always assumed to be within the 
//       same cell and all adjacent cells, that breaks down if entities can spread across more 
//       than two cells horizontally or vertically
class SpatialHashMap
{
   using Cell = size_t;

   Pixels m_level_width;
   Pixels m_level_height;
   Pixels m_cell_width;
   Pixels m_cell_height;
   size_t m_num_x_cells;
   size_t m_num_y_cells;

   std::vector<std::set<EntityId>> m_cells;
   std::unordered_map<EntityId, Cell> m_entity_cell_map;

public:

   SpatialHashMap(); // Should not really be used
   SpatialHashMap(Pixels i_level_width, 
                  Pixels i_level_height, 
                  Pixels i_cell_width, 
                  Pixels i_cell_height);
   virtual ~SpatialHashMap() = default;

   auto get_width() const { return m_level_width; }
   auto get_height() const { return m_level_height; }
   auto get_cell_width() const { return m_cell_width; }
   auto get_cell_height() const { return m_cell_height; }

   bool contains_entity(EntityId i_id) const;
   std::vector<EntityId> get_neighbors(EntityId i_id) const;
   // std::vector<EntityId> get_neighbors(FRect i_area) const;

   extended_opt<Cell> add_entity(EntityId i_id, FPosition i_position);
   extended_opt<Cell> move_entity(EntityId i_id, FPosition i_position);
   extended_opt<Cell> remove_entity(EntityId i_id);

private:

   extended_opt<Cell> get_cell_for_position(Position i_position) const;
   extended_opt<Cell> get_cell_for_position(FPosition i_position) const;
   std::vector<Cell> get_neighboring_cells(Cell i_cell) const;
//    std::vector<Cell> get_neighboring_cells(const Rect& i_frame) const;

};