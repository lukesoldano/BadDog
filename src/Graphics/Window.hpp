#pragma once

#include "Renderer.hpp"
#include "Surface.hpp"

#include <memory>
#include <optional>

// Forward declarations
class SDL_Window;

namespace Graphics
{

// @warning This class is not thread safe
class Window
{
public:

   Window() = delete;
   Window(const Window&) = delete;
   Window(Window&&);

   virtual ~Window();

   Window& operator=(const Window&) = delete;
   Window& operator=(Window&&);

   static std::optional<Window> create();

   // @warning Teardown any window before exiting the SDL for the sake of cleanliness
   void teardown();

   Renderer& get_renderer() const;

   // std::optional<Surface> get_current_surface() const;
   void update_surface();

private:

   Window(SDL_Window* i_sdl_window, Renderer&& i_renderer);

   void teardown_internal();

   SDL_Window* m_sdl_window = nullptr;
   std::unique_ptr<Renderer> m_renderer;

};

} // namespace Window