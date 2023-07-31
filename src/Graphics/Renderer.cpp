#include "Renderer.hpp"

#include "ProjectMacros.hpp"

#include "SDL.h"

using namespace Graphics;

Renderer::Renderer(SDL_Window* i_sdl_window)
{
   m_sdl_renderer = SDL_CreateRenderer(i_sdl_window, -1, SDL_RENDERER_ACCELERATED);
   if (nullptr == m_sdl_renderer) 
   {
      ASSERT(std::string("Failed to create a Renderer, SDL error: ") + SDL_GetError());
   }
}

Renderer::Renderer(Renderer&& other) :
   m_sdl_renderer(other.m_sdl_renderer)
{
   other.m_sdl_renderer = nullptr;
}

Renderer::~Renderer()
{
   if (nullptr != m_sdl_renderer)
   {
      SDL_DestroyRenderer(m_sdl_renderer);
   }
}

Renderer& Renderer::operator=(Renderer&& rhs)
{
   if (this != &rhs)
   {
      this->m_sdl_renderer = rhs.m_sdl_renderer;
      rhs.m_sdl_renderer = nullptr;
   }

   return *this;
}

bool Renderer::render_present()
{
   CHECK_IF_POINTER_VALID_RETURN_FALSE(m_sdl_renderer);
   SDL_RenderPresent(m_sdl_renderer);
   SDL_RenderClear(m_sdl_renderer);
   return true;
}

// bool Renderer::render(RenderInstruction_t&& i_render_instruction)
// {
//    CHECK_IF_POINTER_VALID_RETURN_BOOL(m_sdl_renderer);
//    return i_render_instruction(*m_sdl_renderer);
// }

// bool Renderer::render(std::vector<RenderInstruction_t>&& i_render_instructions)
// {
//    CHECK_IF_POINTER_VALID_RETURN_BOOL(m_sdl_renderer);

//    bool o_all_renders_successful = true;
//    for (const auto& instruction : i_render_instructions)
//    {
//       o_all_renders_successful &= instruction(*m_sdl_renderer);
//    }
//    return o_all_renders_successful;
// }

// std::optional<RgbaColor> Renderer::get_draw_color() const
// {
//    CHECK_IF_POINTER_VALID_RETURN_NULLOPT(m_sdl_renderer);

//    RgbaColor o_color;
//    if (0 != SDL_GetRenderDrawColor(m_sdl_renderer, 
//                                    &o_color.m_r, 
//                                    &o_color.m_g, 
//                                    &o_color.m_b, 
//                                    &o_color.m_a))
//    {
//       LOG_WARNING("Failed to get draw color, SDL Error: " << SDL_GetError());
//       return std::nullopt;
//    }

//    return o_color;
// }

// bool Renderer::set_draw_color(RgbaColor i_color)
// {
//    CHECK_IF_POINTER_VALID_RETURN_BOOL(m_sdl_renderer);

//    if (0 != SDL_SetRenderDrawColor(m_sdl_renderer, 
//                                    i_color.m_r, 
//                                    i_color.m_g, 
//                                    i_color.m_b, 
//                                    i_color.m_a))
//    {
//       LOG_WARNING("Failed to set draw color, SDL Error: " << SDL_GetError());
//       return false;
//    }

//    return true;
// }

// // @TODO Refactor once we change how Surface provides SDL_Surface* more cleverly
// std::optional<Texture> Renderer::create_texture_from_surface(Surface&& i_surface)
// {
//    auto sdl_surface = i_surface.get_sdl_surface();

//    CHECK_IF_POINTER_VALID_RETURN_NULLOPT(m_sdl_renderer);
//    CHECK_IF_POINTER_VALID_RETURN_NULLOPT(sdl_surface);

//    auto texture = SDL_CreateTextureFromSurface(m_sdl_renderer, sdl_surface);
//    if (nullptr == texture)
//    {
//       LOG_ERROR("Failed to create an SDL texture from surface, SDL error: " << SDL_GetError());
//       return std::nullopt;
//    }

//    return std::optional<Texture>({texture, sdl_surface->w, sdl_surface->h});
// }