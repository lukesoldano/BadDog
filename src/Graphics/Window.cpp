#include "Window.hpp"

#include "ProjectDefaults.hpp"
#include "ProjectMacros.hpp"

#include "SDL.h"

using namespace Graphics;

Window::Window()
{
   auto m_sdl_window = SDL_CreateWindow(Defaults::WINDOW_NAME,
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        Defaults::WINDOW_WIDTH, 
                                        Defaults::WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);
   if (nullptr == m_sdl_window)
   {
      ASSERT(std::string("Failed to create an SDL window, SDL error: ") + SDL_GetError());
   }

   m_renderer = std::make_unique<Renderer>(m_sdl_window);

   // Make sure window surface is loaded, even if we don't care about it at this moment otherwise
   SDL_GetWindowSurface(m_sdl_window);
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
   m_renderer.reset();

   if (nullptr != m_sdl_window)
   {
      SDL_DestroyWindow(m_sdl_window);
      m_sdl_window = nullptr;
   }
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

Renderer& Window::get_renderer() const
{
   return *m_renderer.get();
}

void Window::update_surface()
{
   SDL_UpdateWindowSurface(m_sdl_window);
}

