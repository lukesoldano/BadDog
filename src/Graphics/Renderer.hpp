#pragma once

#include "GraphicsDefs.hpp"
#include "Surface.hpp"
#include "Texture.hpp"

#include <functional>
#include <optional>
#include <vector>

// Forward declarations
class SDL_Window;
class SDL_Renderer;

namespace Graphics
{

// @warning This class is not thread safe
class Renderer
{
public:

   Renderer() = delete;
   Renderer(const Renderer&) = delete;
   Renderer(Renderer&&);

   virtual ~Renderer();

   Renderer& operator=(const Renderer&) = delete;
   Renderer& operator=(Renderer&&);

   static std::optional<Renderer> create(SDL_Renderer* i_sdl_renderer);

   bool render_present();

   // @TODO Consider if RenderInstructions with internal SDL logic and access to SDL_Renderer are
   //       the best course of action
   // @TODO Consider adding universal ref with concepts to limit to RenderInstruction_t (or other
   //       solution) as well as iterable container of RenderInstruction_t so vector not required
   //       as well
   bool render(RenderInstruction_t&& i_render_instruction);
   bool render(std::vector<RenderInstruction_t>&& i_render_instructions);

   std::optional<RgbaColor> get_draw_color() const;
   bool set_draw_color(RgbaColor i_color);

   // @TODO Refactor once we change how Surface provides SDL_Surface* more cleverly
   std::optional<Texture> create_texture_from_surface(Surface&& i_surface);
   
private:

   Renderer(SDL_Renderer* i_sdl_renderer);

   SDL_Renderer* m_sdl_renderer = nullptr;

};

} // namespace Graphics