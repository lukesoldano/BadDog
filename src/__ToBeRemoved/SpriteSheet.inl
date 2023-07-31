// Inlined within SpatialHashMap.hpp

#include <assert.h>
#include <utility>

template <size_t NUM_ROWS, size_t NUM_COLUMNS>
SpriteSheet<NUM_ROWS, NUM_COLUMNS>::SpriteSheet(Texture&& i_texture) :
   m_texture(std::move(i_texture)),
   m_frame_width(m_texture.get_width() / NUM_COLUMNS),
   m_frame_height(m_texture.get_height() / NUM_ROWS)
{
   CHECK_CONDITION(m_texture.get_width() > 0);
   CHECK_CONDITION(m_texture.get_height() > 0);
   CHECK_CONDITION(m_texture.get_width() % NUM_COLUMNS == 0);
   CHECK_CONDITION(m_texture.get_height() % NUM_ROWS == 0);
}

template <size_t NUM_ROWS, size_t NUM_COLUMNS>
const Texture& SpriteSheet<NUM_ROWS, NUM_COLUMNS>::get_texture() const
{
   return m_texture;
}

template <size_t NUM_ROWS, size_t NUM_COLUMNS>
Rect SpriteSheet<NUM_ROWS, NUM_COLUMNS>::get_frame(const size_t i_row, const size_t i_column) const
{
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(i_row < NUM_ROWS);
   CHECK_CONDITION_RETURN_EMPTY_INITIALIZER(i_column < NUM_COLUMNS);
   return {int(i_column * m_frame_width), 
           int(i_row * m_frame_height), 
           int(m_frame_width), 
           int(m_frame_height)};
}