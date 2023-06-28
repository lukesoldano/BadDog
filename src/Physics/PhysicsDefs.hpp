#pragma once

#include <utility>

namespace Physics
{

   struct XYPosition
   {
      int x = 0;
      int y = 0;
   };

   using DisplacementVector_t = std::pair<int, int>;

} // namespace Physics