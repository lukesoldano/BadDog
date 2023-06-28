#pragma once

#include "PhysicsDefs.hpp"
#include "ProjectDefs.hpp"

#include <algorithm>
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
template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
class SpatialHashMap
{
   static_assert(X_CELLS != 0, "SpatialHashMap must have at least one x-i_cell");
   static_assert(Y_CELLS != 0, "SpatialHashMap must have at least one y-i_cell");
   static_assert(WIDTH != 0, "SpatialHashMap must have a non-zero width");
   static_assert(HEIGHT != 0, "SpatialHashMap must have at non-zero height");
   static_assert(WIDTH % X_CELLS == 0, "SpatialHashMap width should be divisible by # of x-cells");
   static_assert(HEIGHT % Y_CELLS == 0, "SpatialHashMap height should be divisible by # of y-cells");

   std::array<std::set<EntityId_t>, X_CELLS * Y_CELLS> m_cells;
   std::unordered_map<EntityId_t, SpatialHashMapCell_t> m_entity_cell_map;

public:

   SpatialHashMap() = default;
   virtual ~SpatialHashMap() = default;

   bool contains_entity(EntityId_t i_id) const;

   std::optional<SpatialHashMapCell_t> add_entity(EntityId_t i_id, XYPosition i_position);
   std::optional<SpatialHashMapCell_t> move_entity(EntityId_t i_id, XYPosition i_position);
   std::optional<SpatialHashMapCell_t> remove_entity(EntityId_t i_id);

   std::vector<EntityId_t> get_neighbors(EntityId_t i_id) const;

private:

   std::optional<SpatialHashMapCell_t> get_cell_for_position(XYPosition i_position) const;
   std::vector<SpatialHashMapCell_t> get_neighboring_cells(SpatialHashMapCell_t i_cell) const;

};

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
bool SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::contains_entity(EntityId_t i_id) const
{
   return m_entity_cell_map.contains(i_id);
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::add_entity(EntityId_t i_id, 
                                                                                                XYPosition i_position)
{
   CHECK_CONDITION_RETURN_NULLOPT(!contains_entity(i_id));

   const auto o_cell = get_cell_for_position(i_position);
   CHECK_CONDITION_RETURN_NULLOPT(o_cell.has_value());

   m_cells[o_cell.value()].insert(i_id);
   m_entity_cell_map.emplace(i_id, o_cell.value());
   return o_cell;
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::move_entity(EntityId_t i_id, 
                                                                                                 XYPosition i_position)
{
   CHECK_CONDITION_RETURN_NULLOPT(contains_entity(i_id));

   const auto o_cell = get_cell_for_position(i_position);
   CHECK_CONDITION_RETURN_NULLOPT(o_cell.has_value());

   if (m_entity_cell_map[i_id] == o_cell.value()) return o_cell;

   m_cells[m_entity_cell_map[i_id]].erase(i_id);
   m_entity_cell_map[i_id] = o_cell.value();
   m_cells[o_cell.value()].insert(i_id);
   return o_cell;
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::remove_entity(EntityId_t i_id)
{
   CHECK_CONDITION_RETURN_NULLOPT(contains_entity(i_id));
   const auto o_cell = std::move(m_entity_cell_map[i_id]);
   m_cells[o_cell].erase(i_id);
   m_entity_cell_map.erase(i_id);
   return std::optional<SpatialHashMapCell_t>(std::move(o_cell));
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::vector<EntityId_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::get_neighbors(EntityId_t i_id) const
{
   const auto it = m_entity_cell_map.find(i_id);
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER((it != m_entity_cell_map.cend()));

   // Add entities in the same cell 
   std::vector<EntityId_t> o_neighboring_entities;
   const auto& cell = it->second;
   std::copy_if(m_cells[cell].cbegin(),
                m_cells[cell].cend(),
                std::back_inserter(o_neighboring_entities),
                [&i_id](const auto& entity){ return entity != i_id; });

   // Add neighboring cell entities
   for (const auto& neighbor_cell : get_neighboring_cells(cell))
   {
      o_neighboring_entities.insert(o_neighboring_entities.end(),
                                    m_cells[neighbor_cell].cbegin(), 
                                    m_cells[neighbor_cell].cend());
   }

   return o_neighboring_entities;
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::get_cell_for_position(XYPosition i_position) const
{
   if (WIDTH <= i_position.x || HEIGHT <= i_position.y) return std::nullopt;
   return X_CELLS * int((i_position.y * Y_CELLS) / HEIGHT) + int((i_position.x * X_CELLS) / WIDTH);
}

template <size_t X_CELLS, size_t Y_CELLS, size_t WIDTH, size_t HEIGHT>
std::vector<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS, WIDTH, HEIGHT>::get_neighboring_cells(SpatialHashMapCell_t i_cell) const
{
   if (1 == X_CELLS * Y_CELLS) return {};

   // Case for one dimmensional grid  
   if (1 == X_CELLS || 1 == Y_CELLS)
   {
      if (0 == i_cell) return { i_cell + 1 };
      if (X_CELLS * Y_CELLS - 1 == i_cell) return { i_cell - 1 };
      return { i_cell - 1, i_cell + 1 };
   }

   // Case for two dimmensional grid
   std::vector<SpatialHashMapCell_t> o_neighboring_cells;
   const auto bordering_left = i_cell % X_CELLS == 0;
   const auto bordering_right = !bordering_left && (i_cell - (X_CELLS - 1) % X_CELLS == 0);

   //// Row above
   if (i_cell >= X_CELLS)
   {
      if (!bordering_left) o_neighboring_cells.emplace_back(i_cell - 1 - X_CELLS);
      o_neighboring_cells.emplace_back(i_cell - X_CELLS);
      if (!bordering_right) o_neighboring_cells.emplace_back(i_cell + 1 - X_CELLS);
   }

   //// Same row
   if (!bordering_left) o_neighboring_cells.emplace_back(i_cell - 1);
   if (!bordering_right) o_neighboring_cells.emplace_back(i_cell + 1);

   //// Row below
   if (i_cell <= (X_CELLS * Y_CELLS - 1) - X_CELLS)
   {
      if (!bordering_left) o_neighboring_cells.emplace_back(i_cell - 1 + X_CELLS);
      o_neighboring_cells.emplace_back(i_cell + X_CELLS);
      if (!bordering_right) o_neighboring_cells.emplace_back(i_cell + 1 + X_CELLS);
   }

   return o_neighboring_cells;
}
   
} // namespace Physics