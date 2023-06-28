#pragma once

#include "PhysicsDefs.hpp"
#include "ProjectDefs.hpp"

#include <array>
#include <optional>
#include <set>

namespace Physics
{

using SpatialHashMapCell_t = size_t;

// @warning This class is not thread safe
template <size_t X_CELLS, size_t Y_CELLS>
class SpatialHashMap
{
   size_t m_width;
   size_t m_height;
   std::array<std::set<EntityId_t>, X_CELLS * Y_CELLS> m_cells;
   std::set<EntityId_t> m_mapped_entities;

public:

   SpatialHashMap() = delete;
   SpatialHashMap(size_t width, size_t height);
   virtual ~SpatialHashMap() = default;

   std::optional<SpatialHashMapCell_t> add_entity(EntityId_t id, XYPosition position);

private:

   std::optional<SpatialHashMapCell_t> get_cell(XYPosition position);

};

template <size_t X_CELLS, size_t Y_CELLS>
SpatialHashMap<X_CELLS, Y_CELLS>::SpatialHashMap(size_t width, size_t height) :
   m_width(width),
   m_height(height)
{
   // TODO assert if dimmensions don't make sense with x and y
}

template <size_t X_CELLS, size_t Y_CELLS>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS>::add_entity(EntityId_t id, 
                                                                                 XYPosition position)
{
   if (m_mapped_entities.contains(id)) return std::nullopt;

   auto cell = get_cell(position);
   if (!cell.has_value()) return std::nullopt;

   m_cells[cell.value()].insert(id);
   m_mapped_entities.insert(id);
   return cell;
}

template <size_t X_CELLS, size_t Y_CELLS>
std::optional<SpatialHashMapCell_t> SpatialHashMap<X_CELLS, Y_CELLS>::get_cell(XYPosition position)
{
   if (m_width <= position.x || m_height <= position.y) return std::nullopt;

   return (position.x / 10 + 10 * (position.y / 10));
}
   
} // namespace Physics