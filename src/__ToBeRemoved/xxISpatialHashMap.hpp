#pragma once

#include "ExtendedOptional.hpp"
#include "ProjectDefs.hpp"

#include <vector>

namespace Physics
{  

using SpatialHashMapCell_t = size_t;

class ISpatialHashMap
{
public:

   ISpatialHashMap() = default;
   virtual ~ISpatialHashMap() = default;

   virtual size_t get_width() const = 0;
   virtual size_t get_height() const = 0;
   virtual size_t get_cell_width() const = 0;
   virtual size_t get_cell_height() const = 0;

   virtual bool contains_entity(EntityId i_id) const = 0;
   virtual std::vector<EntityId> get_neighbors(EntityId i_id) const = 0;
   virtual std::vector<EntityId> get_neighbors(FRect i_area) const = 0;

   virtual extended_opt<SpatialHashMapCell_t> add_entity(EntityId i_id, FPoint i_position) = 0;
   virtual extended_opt<SpatialHashMapCell_t> add_entity(EntityId i_id, FRect i_position) = 0;

   virtual extended_opt<SpatialHashMapCell_t> move_entity(EntityId i_id, FPoint i_position) = 0;
   virtual extended_opt<SpatialHashMapCell_t> move_entity(EntityId i_id, FRect i_position) = 0;

   virtual extended_opt<SpatialHashMapCell_t> remove_entity(EntityId i_id) = 0;

};

} // namespace Physics