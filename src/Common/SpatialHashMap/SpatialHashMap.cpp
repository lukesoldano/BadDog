#include "SpatialHashMap.hpp"

#include "ProjectMacros.hpp"

#include <algorithm>

SpatialHashMap::SpatialHashMap() :
   SpatialHashMap(1, 1, 1, 1)
{
}

SpatialHashMap::SpatialHashMap(Pixels i_level_width, 
                               Pixels i_level_height, 
                               Pixels i_cell_width, 
                               Pixels i_cell_height) :
   m_level_width(i_level_width),
   m_level_height(i_level_height),
   m_cell_width(i_cell_width),
   m_cell_height(i_cell_height),
   m_num_x_cells(i_level_width / i_cell_width),
   m_num_y_cells(i_level_height / i_cell_height),
   m_cells(m_num_x_cells * m_num_y_cells)
{
   CHECK_CONDITION(m_cell_width > 0 && "SpatialHashMap cannot have cells of <= 0 width");
   CHECK_CONDITION(m_cell_height > 0 && "SpatialHashMap cannot have cells of <= 0 height");
   CHECK_CONDITION(m_level_width > 0 && "SpatialHashMap must have a positive level width");
   CHECK_CONDITION(m_level_height > 0 && "SpatialHashMap must have a positive level height");
   CHECK_CONDITION(m_level_width % m_cell_width == 0 && "SpatialHashMap level width should be divisible by cell width");
   CHECK_CONDITION(m_level_height % m_cell_height == 0 && "SpatialHashMap level height should be divisible by cell height");
}

bool SpatialHashMap::contains_entity(EntityId i_id) const
{
   return m_entity_cell_map.contains(i_id);
}

std::vector<EntityId> SpatialHashMap::get_neighbors(EntityId i_id) const
{
   const auto it = m_entity_cell_map.find(i_id);
   CHECK_CONDITION_RETURN_VALUE(it != m_entity_cell_map.cend(), {});

   // Add entities in the same cell 
   std::vector<EntityId> neighboring_entities;
   const auto& cell = it->second;
   std::copy_if(m_cells[cell].cbegin(),
                m_cells[cell].cend(),
                std::back_inserter(neighboring_entities),
                [&i_id](const auto& entity){ return entity != i_id; });

   // Add neighboring cell entities
   for (const auto& neighbor_cell : get_neighboring_cells(cell))
   {
      neighboring_entities.insert(neighboring_entities.end(),
                                  m_cells[neighbor_cell].cbegin(), 
                                  m_cells[neighbor_cell].cend());
   }

   return neighboring_entities;
}

// std::vector<EntityId> SpatialHashMap::get_neighbors(FRect i_area) const
// {
//    auto area = i_area.to_rect();
//    CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(area.x >= 0 && area.x + area.w <= m_level_width);
//    CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(area.y >= 0 && area.y + area.h <= m_level_height);

//    // Add entities from cells that the area has overlap with
//    std::vector<EntityId> o_neighboring_entities;

//    // Simplify the math by stretching the area to encapsulate the entirety of the relevant cells
//    area.w += (area.w % m_cell_width == 0 ? 0 : m_cell_width - ((area.x + area.w) % m_cell_width));
//    area.h += (area.h % m_cell_height == 0 ? 0 : m_cell_height - ((area.y + area.h) % m_cell_height));
//    area.x = area.x - (area.x % m_cell_width);
//    area.y = area.y - (area.y % m_cell_height);

//    const auto origin_cell = get_cell_for_position(area.get_origin());
//    CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(origin_cell.has_value());

//    // Add entities within the frame
//    for (auto i=0; i<area.w/m_cell_width; ++i)
//    {
//       for (auto j=0; j<area.h/m_cell_height; ++j)
//       {
//          const auto cell = origin_cell.value() + i + (j * m_num_x_cells);
//          std::copy(m_cells[cell].cbegin(),
//                    m_cells[cell].cend(),
//                    std::back_inserter(o_neighboring_entities));
//       }
//    }

//    // Add all entities from neighboring cells
//    for (const auto& neighbor_cell : get_neighboring_cells(area))
//    {
//       o_neighboring_entities.insert(o_neighboring_entities.end(),
//                                     m_cells[neighbor_cell].cbegin(), 
//                                     m_cells[neighbor_cell].cend());
//    }

//    return o_neighboring_entities;
// }

extended_opt<SpatialHashMap::Cell> SpatialHashMap::add_entity(EntityId i_id, FPosition i_position)
{
   CHECK_CONDITION_RETURN_VALUE(!contains_entity(i_id), std::nullopt);

   const auto cell = get_cell_for_position(i_position);
   CHECK_CONDITION_RETURN_VALUE(cell.has_value(), std::nullopt);

   m_cells[cell.value()].insert(i_id);
   m_entity_cell_map.emplace(i_id, cell.value());
   return cell;
}

extended_opt<SpatialHashMap::Cell> SpatialHashMap::move_entity(EntityId i_id, FPosition i_position)
{
   CHECK_CONDITION_RETURN_VALUE(contains_entity(i_id), std::nullopt);

   const auto cell = get_cell_for_position(i_position);
   CHECK_CONDITION_RETURN_VALUE(cell.has_value(), std::nullopt);

   if (m_entity_cell_map[i_id] == cell.value()) return cell;

   m_cells[m_entity_cell_map[i_id]].erase(i_id);
   m_entity_cell_map[i_id] = cell.value();
   m_cells[cell.value()].insert(i_id);

   return cell;
}

extended_opt<SpatialHashMap::Cell> SpatialHashMap::remove_entity(EntityId i_id)
{
   CHECK_CONDITION_RETURN_VALUE(contains_entity(i_id), std::nullopt);

   const auto cell = std::move(m_entity_cell_map[i_id]);
   m_cells[cell].erase(i_id);
   m_entity_cell_map.erase(i_id);

   return extended_opt<Cell>(std::move(cell));
}

extended_opt<SpatialHashMap::Cell> SpatialHashMap::get_cell_for_position(Position i_position) const
{
   if (m_level_width <= i_position.m_x || m_level_height <= i_position.m_y) return std::nullopt;
   return m_num_x_cells * 
          ((i_position.m_y * m_num_y_cells) / m_level_height) + 
          ((i_position.m_x * m_num_x_cells) / m_level_width);
}

extended_opt<SpatialHashMap::Cell> SpatialHashMap::get_cell_for_position(FPosition i_position) const
{
   return get_cell_for_position(i_position.to_position());
}

std::vector<SpatialHashMap::Cell> SpatialHashMap::get_neighboring_cells(Cell i_cell) const
{
   if (m_cell_width == m_level_width && m_cell_height == m_level_height) return {};

   std::vector<Cell> neighboring_cells;
   const auto bordering_left = i_cell % m_num_x_cells == 0;
   const auto bordering_right = ((i_cell - m_num_x_cells + 1) % m_num_x_cells) == 0;

   //// Row above
   if (i_cell >= m_num_x_cells)
   {
      if (!bordering_left) neighboring_cells.emplace_back(i_cell - 1 - m_num_x_cells);
      neighboring_cells.emplace_back(i_cell - m_num_x_cells);
      if (!bordering_right) neighboring_cells.emplace_back(i_cell + 1 - m_num_x_cells);
   }

   //// Same row
   if (!bordering_left) neighboring_cells.emplace_back(i_cell - 1);
   if (!bordering_right) neighboring_cells.emplace_back(i_cell + 1);

   //// Row below
   if (i_cell <= (m_num_x_cells * m_num_y_cells - 1) - m_num_x_cells)
   {
      if (!bordering_left) neighboring_cells.emplace_back(i_cell - 1 + m_num_x_cells);
      neighboring_cells.emplace_back(i_cell + m_num_x_cells);
      if (!bordering_right) neighboring_cells.emplace_back(i_cell + 1 + m_num_x_cells);
   }

   return neighboring_cells;
}

// // This function should only be called with a frame that has been stretched to fill
// // the entirety of its respective cells
// std::vector<Cell> SpatialHashMap::get_neighboring_cells(const Rect& i_frame) const
// {
//    if (m_cell_width == m_level_width && m_cell_height == m_level_height) return {};

//    const Point frame_origin{i_frame.get_origin()};
//    const auto top_left_corner_cell = get_cell_for_position(frame_origin);
//    CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(top_left_corner_cell.has_value());

//    const bool bordering_top = top_left_corner_cell.value() < m_num_x_cells;
//    const bool bordering_left = top_left_corner_cell.value() % m_num_x_cells == 0;

//    auto bottom_right_corner = frame_origin;
//    bottom_right_corner.x += i_frame.w - 1;
//    bottom_right_corner.y += i_frame.h - 1;

//    const auto bottom_right_corner_cell = get_cell_for_position(bottom_right_corner);
//    CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(bottom_right_corner_cell.has_value());

//    const bool bordering_bottom{(m_num_x_cells * (m_num_y_cells - 1)) <= bottom_right_corner_cell.value()};
//    const bool bordering_right{((bottom_right_corner_cell.value() - m_num_x_cells + 1) % m_num_x_cells) == 0};

//    const size_t frame_cell_width = i_frame.w / m_cell_width; // leverages truncation

//    std::vector<Cell> o_neighboring_cells;
//    if (!bordering_top) 
//    {
//       if (!bordering_left) o_neighboring_cells.emplace_back(top_left_corner_cell.value() - m_num_x_cells - 1);
//       if (!bordering_right) o_neighboring_cells.emplace_back(top_left_corner_cell.value() + frame_cell_width - m_num_x_cells);
   
//       for (auto i = top_left_corner_cell.value() - m_num_x_cells; 
//            i <= top_left_corner_cell.value() + frame_cell_width - m_num_x_cells - 1;
//            ++i)
//       {
//          o_neighboring_cells.emplace_back(i);
//       }
//    }

//    if (!bordering_bottom) 
//    {
//       if (!bordering_left) o_neighboring_cells.emplace_back(bottom_right_corner_cell.value() - frame_cell_width + m_num_x_cells);
//       if (!bordering_right) o_neighboring_cells.emplace_back(bottom_right_corner_cell.value() + m_num_x_cells + 1);
   
//       for (auto i = bottom_right_corner_cell.value() - frame_cell_width + m_num_x_cells + 1; 
//            i <= bottom_right_corner_cell.value() + m_num_x_cells;
//            ++i)
//       {
//          o_neighboring_cells.emplace_back(i);
//       }
//    }

//    if (!bordering_left)
//    {
//       for (auto i = 0; i < i_frame.h / m_cell_height; ++i)
//       {
//          o_neighboring_cells.emplace_back(top_left_corner_cell.value() - 1 + i * m_num_x_cells);
//       }
//    }

//    if (!bordering_right)
//    {
//       for (auto i = 0; i < i_frame.h / m_cell_height; ++i)
//       {
//          o_neighboring_cells.emplace_back(top_left_corner_cell.value() + frame_cell_width + i * m_num_x_cells);
//       }
//    }

//    return o_neighboring_cells;
// }