// Inlined within SpatialHashMap.hpp

#include <algorithm>

// All below #defines will be undefined at the bottom of this file
// Merely a dumb helper to shorten the otherwise ludicrously long function specifiers
#define SHM SpatialHashMap<LEVEL_WIDTH, LEVEL_HEIGHT, CELL_WIDTH, CELL_HEIGHT>

#define X_CELLS (LEVEL_WIDTH / CELL_WIDTH)
#define Y_CELLS (LEVEL_HEIGHT / CELL_HEIGHT)

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
bool SHM::contains_entity(EntityId i_id) const
{
   return m_entity_cell_map.contains(i_id);
}

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
std::vector<EntityId> SHM::get_neighbors(EntityId i_id) const
{
   const auto it = m_entity_cell_map.find(i_id);
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER((it != m_entity_cell_map.cend()));

   // Add entities in the same cell 
   std::vector<EntityId> o_neighboring_entities;
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

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
std::vector<EntityId> SHM::get_neighbors(FRect i_area) const
{
   auto area = i_area.to_rect();
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(area.x >= 0 && area.x + area.w <= LEVEL_WIDTH);
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(area.y >= 0 && area.y + area.h <= LEVEL_HEIGHT);

   // Add entities from cells that the area has overlap with
   std::vector<EntityId> o_neighboring_entities;

   // Simplify the math by stretching the area to encapsulate the entirety of the relevant cells
   area.w += (area.w % CELL_WIDTH == 0 ? 0 : CELL_WIDTH - ((area.x + area.w) % CELL_WIDTH));
   area.h += (area.h % CELL_HEIGHT == 0 ? 0 : CELL_HEIGHT - ((area.y + area.h) % CELL_HEIGHT));
   area.x = area.x - (area.x % CELL_WIDTH);
   area.y = area.y - (area.y % CELL_HEIGHT);

   const auto origin_cell = get_cell_for_position(area.get_origin());
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(origin_cell.has_value());

   // Add entities within the frame
   for (auto i=0; i<area.w/CELL_WIDTH; ++i)
   {
      for (auto j=0; j<area.h/CELL_HEIGHT; ++j)
      {
         const auto cell = origin_cell.value() + i + (j * X_CELLS);
         std::copy(m_cells[cell].cbegin(),
                   m_cells[cell].cend(),
                   std::back_inserter(o_neighboring_entities));
      }
   }

   // Add all entities from neighboring cells
   for (const auto& neighbor_cell : get_neighboring_cells(area))
   {
      o_neighboring_entities.insert(o_neighboring_entities.end(),
                                    m_cells[neighbor_cell].cbegin(), 
                                    m_cells[neighbor_cell].cend());
   }

   return o_neighboring_entities;
}

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
extended_opt<SpatialHashMapCell_t> SHM::add_entity(EntityId i_id, FPoint i_position)
{
   CHECK_CONDITION_RETURN_NULLOPT(!contains_entity(i_id));

   const auto o_cell = get_cell_for_position(i_position);
   CHECK_CONDITION_RETURN_NULLOPT(o_cell.has_value());

   m_cells[o_cell.value()].insert(i_id);
   m_entity_cell_map.emplace(i_id, o_cell.value());
   return o_cell;
}

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
extended_opt<SpatialHashMapCell_t> SHM::add_entity(EntityId i_id, FRect i_rect)
{
   CHECK_CONDITION_RETURN_NULLOPT(i_rect.to_rect().w <= CELL_WIDTH);
   CHECK_CONDITION_RETURN_NULLOPT(i_rect.to_rect().h <= CELL_HEIGHT);
   return add_entity(i_id, FPoint{i_rect.x + (i_rect.w  / 2.0f), i_rect.y + (i_rect.h / 2.0f)});
}

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
extended_opt<SpatialHashMapCell_t> SHM::move_entity(EntityId i_id, FPoint i_position)
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

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
extended_opt<SpatialHashMapCell_t> SHM::move_entity(EntityId i_id, FRect i_rect)
{
   CHECK_CONDITION_RETURN_NULLOPT(i_rect.to_rect().w <= CELL_WIDTH);
   CHECK_CONDITION_RETURN_NULLOPT(i_rect.to_rect().h <= CELL_HEIGHT);
   return move_entity(i_id, FPoint{i_rect.x + (i_rect.w  / 2.0f), i_rect.y + (i_rect.h / 2.0f)});
}

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
extended_opt<SpatialHashMapCell_t> SHM::remove_entity(EntityId i_id)
{
   CHECK_CONDITION_RETURN_NULLOPT(contains_entity(i_id));
   const auto o_cell = std::move(m_entity_cell_map[i_id]);
   m_cells[o_cell].erase(i_id);
   m_entity_cell_map.erase(i_id);
   return extended_opt<SpatialHashMapCell_t>(std::move(o_cell));
}

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
extended_opt<SpatialHashMapCell_t> SHM::get_cell_for_position(Point i_position) const
{
   if (LEVEL_WIDTH <= i_position.x || LEVEL_HEIGHT <= i_position.y) return std::nullopt;
   return X_CELLS * 
          ((i_position.y * Y_CELLS) / LEVEL_HEIGHT) + 
          ((i_position.x * X_CELLS) / LEVEL_WIDTH);
}

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
extended_opt<SpatialHashMapCell_t> SHM::get_cell_for_position(FPoint i_position) const
{
   return get_cell_for_position(i_position.to_point());
}

template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
std::vector<SpatialHashMapCell_t> SHM::get_neighboring_cells(SpatialHashMapCell_t i_cell) const
{
   if (CELL_WIDTH == LEVEL_WIDTH && CELL_HEIGHT == LEVEL_HEIGHT) return {};

   std::vector<SpatialHashMapCell_t> o_neighboring_cells;
   const auto bordering_left = i_cell % X_CELLS == 0;
   const auto bordering_right = ((i_cell - X_CELLS + 1) % X_CELLS) == 0;

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

// This function should only be called with a frame that has been stretched to fill
// the entirety of its respective cells
template <size_t LEVEL_WIDTH, size_t LEVEL_HEIGHT, size_t CELL_WIDTH, size_t CELL_HEIGHT>
std::vector<SpatialHashMapCell_t> SHM::get_neighboring_cells(const Rect& i_frame) const
{
   if (CELL_WIDTH == LEVEL_WIDTH && CELL_HEIGHT == LEVEL_HEIGHT) return {};

   const Point frame_origin{i_frame.get_origin()};
   const auto top_left_corner_cell = get_cell_for_position(frame_origin);
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(top_left_corner_cell.has_value());

   const bool bordering_top = top_left_corner_cell.value() < X_CELLS;
   const bool bordering_left = top_left_corner_cell.value() % X_CELLS == 0;

   auto bottom_right_corner = frame_origin;
   bottom_right_corner.x += i_frame.w - 1;
   bottom_right_corner.y += i_frame.h - 1;

   const auto bottom_right_corner_cell = get_cell_for_position(bottom_right_corner);
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(bottom_right_corner_cell.has_value());

   const bool bordering_bottom{(X_CELLS * (Y_CELLS - 1)) <= bottom_right_corner_cell.value()};
   const bool bordering_right{((bottom_right_corner_cell.value() - X_CELLS + 1) % X_CELLS) == 0};

   const size_t frame_cell_width = i_frame.w / CELL_WIDTH; // leverages truncation

   std::vector<SpatialHashMapCell_t> o_neighboring_cells;
   if (!bordering_top) 
   {
      if (!bordering_left) o_neighboring_cells.emplace_back(top_left_corner_cell.value() - X_CELLS - 1);
      if (!bordering_right) o_neighboring_cells.emplace_back(top_left_corner_cell.value() + frame_cell_width - X_CELLS);
   
      for (auto i = top_left_corner_cell.value() - X_CELLS; 
           i <= top_left_corner_cell.value() + frame_cell_width - X_CELLS - 1;
           ++i)
      {
         o_neighboring_cells.emplace_back(i);
      }
   }

   if (!bordering_bottom) 
   {
      if (!bordering_left) o_neighboring_cells.emplace_back(bottom_right_corner_cell.value() - frame_cell_width + X_CELLS);
      if (!bordering_right) o_neighboring_cells.emplace_back(bottom_right_corner_cell.value() + X_CELLS + 1);
   
      for (auto i = bottom_right_corner_cell.value() - frame_cell_width + X_CELLS + 1; 
           i <= bottom_right_corner_cell.value() + X_CELLS;
           ++i)
      {
         o_neighboring_cells.emplace_back(i);
      }
   }

   if (!bordering_left)
   {
      for (auto i = 0; i < i_frame.h / CELL_HEIGHT; ++i)
      {
         o_neighboring_cells.emplace_back(top_left_corner_cell.value() - 1 + i * X_CELLS);
      }
   }

   if (!bordering_right)
   {
      for (auto i = 0; i < i_frame.h / CELL_HEIGHT; ++i)
      {
         o_neighboring_cells.emplace_back(top_left_corner_cell.value() + frame_cell_width + i * X_CELLS);
      }
   }

   return o_neighboring_cells;
}

// Kill convenience defines
#undef X_CELLS
#undef Y_CELLS
#undef SHM