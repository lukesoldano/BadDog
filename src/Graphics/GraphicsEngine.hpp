#pragma once

#include "Camera.hpp"
#include "Window.hpp"

#include <memory>

namespace Graphics
{

// @warning This class is not thread safe
class GraphicsEngine
{
   std::unique_ptr<Window> m_window;

public:

   GraphicsEngine() = default;
   virtual ~GraphicsEngine() = default;

   // @warning Throws on failure
   void initialize();

   // @note A symmetrical call to teardown should be made if a call to initialize was made
   void teardown();

   // @warning Throws if m_window has become invalidated
   void render();

};

} // namespace Graphics