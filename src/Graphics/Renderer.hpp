#pragma once

// #include "Texture.hpp"

// #include <vector>

// Forward declarations
class SDL_Renderer;
class SDL_Window;

namespace Graphics
{

// RAII wrapper for an SDL_Renderer
class Renderer
{
   SDL_Renderer* m_sdl_renderer = nullptr;

public:

   Renderer() = delete;
   Renderer(SDL_Window* i_sdl_window);
   Renderer(const Renderer&) = delete;
   Renderer(Renderer&&);

   virtual ~Renderer();

   Renderer& operator=(const Renderer&) = delete;
   Renderer& operator=(Renderer&&);

   bool render_present();

//    std::optional<RgbaColor> get_draw_color() const;
//    bool set_draw_color(RgbaColor i_color);

//    // @TODO Refactor once we change how Surface provides SDL_Surface* more cleverly
//    std::optional<Texture> create_texture_from_surface(Surface&& i_surface);
   
};

} // namespace Graphics