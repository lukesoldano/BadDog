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

// @note The cell areas should be larger than the area of the largest entity in order to take 
//       advantage of this container as an optimization for broad phase collision detection
// @warning This class is not thread safe
template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
class SpatialHashMap
{
   static_assert(X_CELLS != 0, "SpatialHashMap must have at least one x-cell");
   static_assert(Y_CELLS != 0, "SpatialHashMap must have at least one y-cell");
   static_assert(WIDTH != 0, "SpatialHashMap must have a non-zero width");
   static_assert(HEIGHT != 0, "SpatialHashMap must have at non-zero height");
   static_assert(WIDTH % X_CELLS == 0, "SpatialHashMap width should be divisible by # of x-cells");
   static_assert(HEIGHT % Y_CELLS == 0, "SpatialHashMap height should be divisible by # of y-cells");

   std::array<std::set<EntityId_t>, X_CELLS * Y_CELLS> m_cells;
   std::unordered_map<EntityId_t, SpatialHashMapCell_t> m_entity_cell_map;

public:

   SpatialHashMap() = default;
   virtual ~SpatialHashMap() = default;

   bool contains_entity(EntityId_t id) const;


   std::optional<SpatialHashMapCell_t> add_entity(EntityId_t id, XYPosition position);
   std::optional<SpatialHashMapCell_t> move_entity(EntityId_t id, XYPosition position);
   std::optional<SpatialHashMapCell_t> remove_entity(EntityId_t id);

private:

   std::optional<SpatialHashMapCell_t> get_cell_for_position(XYPosition position) const;
   std::vector<SpatialHashMapCell_t> get_neighboring_cells(SpatialHashMapCell_t cell) const;

};

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
bool SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::contains_entity(EntityId_t id) const
{
   return m_entity_cell_map.contains(id);
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::add_entity(EntityId_t id, 
                                                                                                XYPosition position)
{
   if (contains_entity(id)) return std::nullopt;

   auto cell = get_cell_for_position(position);
   if (!cell.has_value()) return std::nullopt;

   m_cells[cell.value()].insert(id);
   m_entity_cell_map.emplace(id, cell.value());
   return cell;
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::move_entity(EntityId_t id, 
                                                                                                 XYPosition position)
{
   if (!contains_entity(id)) return std::nullopt;

   auto cell = get_cell_for_position(position);
   if (!cell.has_value()) return std::nullopt;

   if (m_entity_cell_map[id] == cell.value()) return cell;

   m_cells[m_entity_cell_map[id]].erase(id);
   m_entity_cell_map[id] = cell.value();
   m_cells[cell.value()].insert(id);
   return cell;
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::remove_entity(EntityId_t id)
{
   if (!contains_entity(id)) return std::nullopt;
   auto cell = std::move(m_entity_cell_map[id]);
   m_cells[cell].erase(id);
   m_entity_cell_map.erase(id);
   return std::optional<SpatialHashMapCell_t>(std::move(cell));
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::get_cell_for_position(XYPosition position) const
{
   if (WIDTH <= position.x || HEIGHT <= position.y) return std::nullopt;
   return X_CELLS * int((position.y * Y_CELLS) / HEIGHT) + int((position.x * X_CELLS) / WIDTH);
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::vector<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::get_neighboring_cells(SpatialHashMapCell_t cell) const
{
   if (cell > X_CELLS * Y_CELLS) return {};
   if (1 == X_CELLS * Y_CELLS) return { 0 };
   if (2 == X_CELLS * Y_CELLS) return { 0, 1 };
   if (4 == X_CELLS * Y_CELLS) return { 0, 1, 2, 3 };
   if (1 == X_CELLS || 1 == Y_CELLS)
   {
      if (0 == cell) return { 0, 1 };
      if ((X_CELLS * Y_CELLS) - 1 == cell) return { cell, cell + 1 };
      return { cell - 1, cell, cell + 1 };
   } 
   
   std::vector<SpatialHashMapCell_t> neighboring_cells;
   neighboring_cells.reserve(9); // Max # neighboring cells (self-inclusive) in any n x m grid
   neighboring_cells.emplace_back(cell);
   
   // TODO FINISH

   return neighboring_cells;
}
   
} // namespace Physics