#pragma once

#include "Window.hpp"

#include <memory>

namespace Graphics
{

// @warning This class is not thread safe
// @warning This class should not be sub-classed
class GameGraphics
{
public:

   GameGraphics() = default;
   ~GameGraphics() = default;

   // @warning Throws on failure
   void initialize();

   // @note A symmetrical call to teardown should be made if a call to initialize was made
   void teardown();

   // @warning Throws on failure
   void render();

private:

   std::unique_ptr<Window> m_window;

};

} // namespace Graphics