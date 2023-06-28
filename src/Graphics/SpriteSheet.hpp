#pragma once

#include "ProjectDefs.hpp"
#include "Texture.hpp"

namespace Graphics
{

// This class assumes all sprites have the same dimmensions and that the sprite frames are 
// subdivided equally
template <size_t NUM_ROWS, size_t NUM_COLUMNS>
class SpriteSheet
{
   static_assert(NUM_ROWS != 0, "SpriteSheet must have non-zero row count");
   static_assert(NUM_COLUMNS != 0, "SpriteSheet must have non-zero column count");

   const Texture m_texture;
   const size_t m_frame_width = 0;
   const size_t m_frame_height = 0;

public:

   SpriteSheet() = delete;
   SpriteSheet(Texture&& i_texture);

   virtual ~SpriteSheet() = default;

   const Texture& get_texture() const;
   Rect get_frame(const size_t i_row, const size_t i_column) const;

};

#include "SpriteSheet.inl"

} // namespace Graphics
