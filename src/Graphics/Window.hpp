#pragma once

#include "Renderer.hpp"

#include <memory>

// Forward declarations
class SDL_Window;

namespace Graphics
{

// RAII wrapper for an SDL_Window
class Window
{
   SDL_Window* m_sdl_window = nullptr;
   std::unique_ptr<Renderer> m_renderer;

public:

   Window();
   Window(const Window&) = delete;
   Window(Window&&);

   virtual ~Window();

   Window& operator=(const Window&) = delete;
   Window& operator=(Window&&);

   Renderer& get_renderer() const;

   void update_surface();

};

} // namespace Window