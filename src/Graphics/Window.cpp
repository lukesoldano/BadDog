#include "Window.hpp"

#include "Logger.hpp"
#include "ProjectDefs.hpp"

#include "SDL.h"

#include <assert.h>

using namespace Graphics;

namespace
{
   constexpr auto WINDOW_NAME = "2DPlatformer"; 
   constexpr int DEFAULT_WINDOW_WIDTH = 680;
   constexpr int DEFAULT_WINDOW_HEIGHT = 480;
}

Window::Window(SDL_Window* i_sdl_window, Renderer&& renderer) :
   m_sdl_window(i_sdl_window),
   m_renderer(std::make_unique<Renderer>(std::move(renderer)))
{
   CHECK_IF_POINTER_VALID(i_sdl_window);
}

Window::Window(Window&& other) :
   m_sdl_window(other.m_sdl_window),
   m_renderer(std::move(other.m_renderer))
{
   other.m_sdl_window = nullptr;
   other.m_renderer = nullptr;
}

Window::~Window()
{
   teardown_internal();
}

Window& Window::operator=(Window&& rhs)
{
   if (this != &rhs)
   {
      this->m_sdl_window = rhs.m_sdl_window;
      this->m_renderer = std::move(rhs.m_renderer);
      rhs.m_sdl_window = nullptr;
      rhs.m_renderer = nullptr;
   }

   return *this;
}

std::optional<Window> Window::create()
{
   auto sdl_window = SDL_CreateWindow(WINDOW_NAME,
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      DEFAULT_WINDOW_WIDTH, 
                                      DEFAULT_WINDOW_HEIGHT,
                                      SDL_WINDOW_SHOWN);
   if (nullptr == sdl_window)
   {
      LOG_ERROR("Failed to create an SDL window, SDL error: " << SDL_GetError());
      return std::nullopt;
   }

   auto renderer_optional = Renderer::create(SDL_CreateRenderer(sdl_window, 
                                                                -1, 
                                                                SDL_RENDERER_ACCELERATED));
   if (std::nullopt == renderer_optional)
   {
      LOG_ERROR("Failed to create a Renderer, SDL error: " << SDL_GetError());
      SDL_DestroyWindow(sdl_window);
      return std::nullopt;
   }

   // Make sure window surface is loaded, even if we don't care about it at this moment otherwise
   SDL_GetWindowSurface(sdl_window);

   return std::optional<Window>({sdl_window, std::move(renderer_optional.value())});
}

void Window::teardown()
{
   teardown_internal();
}

void Window::teardown_internal()
{
   m_renderer.reset();

   if (nullptr != m_sdl_window)
   {
      SDL_DestroyWindow(m_sdl_window);
      m_sdl_window = nullptr;
   }
}

Renderer& Window::get_renderer() const
{
   return *m_renderer.get();
}

// std::optional<Surface> Window::get_current_surface() const
// {
//    if (nullptr == m_sdl_window)
//    {
//       LOG_ERROR("m_sdl_window is null");
//       return std::nullopt;
//    }

//    auto surface_optional = Surface::create(SDL_GetWindowSurface(m_sdl_window));
//    if (std::nullopt == surface_optional)
//    {
//       LOG_ERROR("Failed to create a Surface, SDL error: " << SDL_GetError());
//    }

//    return surface_optional;
// }

void Window::update_surface()
{
   SDL_UpdateWindowSurface(m_sdl_window);
}

